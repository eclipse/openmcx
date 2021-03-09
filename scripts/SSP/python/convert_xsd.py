################################################################################
# Copyright (c) 2020 AVL List GmbH and others
# 
# This program and the accompanying materials are made available under the
# terms of the Apache Software License 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0.
# 
# SPDX-License-Identifier: Apache-2.0
################################################################################

import argparse
import errno
import os
import os.path
import re
import sys


_HEADER = """#ifndef {include_guard}
#define {include_guard}

const char {name}[] = {{{content}, 0}};

#endif // !{include_guard}
"""


def simplify_xsd(schema_content):
    # the import is done only in the case XML simplification is actually used.
    # benefit: one can run the script even with a python which does not have lxml
    import lxml.etree

    parser = lxml.etree.XMLParser(remove_blank_text=True, remove_comments=True)
    root = lxml.etree.fromstring(schema_content.encode('utf-8'), parser)
    for elem in root.findall(".//{http://www.w3.org/2001/XMLSchema}annotation"):
        elem.getparent().remove(elem)
    return lxml.etree.tostring(root, encoding='UTF-8', xml_declaration=True).decode('UTF-8')


def convert_xsd_to_c(schema_file, dest_dir, prefix=None, simplify_schema=False):
    # process schema file
    with open(schema_file, "r") as f:
        schema_content = f.read()

    if simplify_schema:
        schema_content = simplify_xsd(schema_content)

    content = ", ".join(str(ord(c)) for c in schema_content)

    # create destination directory
    if dest_dir is not None and not os.path.exists(dest_dir):
        try:
            os.makedirs(dest_dir)
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise
    elif dest_dir is not None and not os.path.isdir(dest_dir):
        raise IOError("Destination '{}' is not a directory".format(dest_dir))

    # generate template arguments
    base_name = os.path.splitext(os.path.basename(schema_file))[0]
    dest_file = "{}.h".format(base_name)
    if dest_dir is not None:
        dest_file = os.path.join(dest_dir, dest_file)

    variable_name = "{}SchemaStr".format(base_name)
    variable_name = variable_name[0].lower() + variable_name[1:]

    # insert '_' before each uppercase letter, except the starting one; and transform all letters to uppercase
    macro_name = re.sub(r'(?<!^)(?=[A-Z])', '_', base_name).upper()
    if prefix is not None:
        # replace path sepearators with underscores to reflect the folder hierarchy
        prefix = re.sub(r'(/|\\)', '_', prefix).upper()
        macro_name = "{}_{}".format(prefix, macro_name)
    macro_name = "MCX_READER_SSP_SCHEMA_{}_H".format(macro_name)

    # write output file
    with open(dest_file, 'w') as f:
        f.write(_HEADER.format(include_guard=macro_name,
                               name=variable_name,
                               content=content))


def main():
    parser = argparse.ArgumentParser(description='Create a C header file with the content of an XSD file',
                                     epilog="The generated header file contains one char array that is "
                                            "initialised with the content of the XSD file.")

    parser.add_argument('schema', type=str, help='XML schema file')
    parser.add_argument('-o', '--outdir', dest='output_dir', type=str, default=None,
                        help='Output directory where the new file will be generated')
    parser.add_argument('-p', '--prefix', dest='prefix', type=str, default=None,
                        help='Prefix used for the include guard definition')
    parser.add_argument('--simplify', dest='simplify_schema', action='store_true',
                        help='Remove annotations and comments from the schema file')

    args = parser.parse_args()

    convert_xsd_to_c(args.schema, args.output_dir, args.prefix, args.simplify_schema)


if __name__ == "__main__":
    main()
