/* ---------------------------------------------------------------------------*
 * Optparse is a public domain, portable, reentrant, embeddable, getopt-like
 * option parser. It supports POSIX getopt option strings, GNU-style long
 * options, argument permutation, and subcommand processing.
 *
 * Copyright: 2014 Christopher Wellons (https://github.com/skeeto)
 * optparse is licensed under the The Unlicense.
 * See https://github.com/skeeto/optparse
 * ---------------------------------------------------------------------------*/
#ifndef OPTPARSE_H
#define OPTPARSE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct optparse {
    int argc;
    char **argv;
    int permute;
    int optind;
    int optopt;
    char *optarg;
    char errmsg[64];
    int subopt;
};

enum optparse_argtype {
    OPTPARSE_NONE,
    OPTPARSE_REQUIRED,
    OPTPARSE_OPTIONAL
};

struct optparse_long {
    const char *longname;
    int shortname;
    enum optparse_argtype argtype;
};


/**
 * Initializes the parser state.
 */
void optparse_init(struct optparse *options, int argc, char **argv);


/**
 * Read the next option in the argv array.
 * @param optstring a getopt()-formatted option string.
 * @return the next option character, -1 for done, or '?' for error
 *
 * Just like getopt(), a character followed by no colons means no
 * argument. One colon means the option has a required argument. Two
 * colons means the option takes an optional argument.
 */
int optparse(struct optparse *options, const char *optstring);


/**
 * Handles GNU-style long options in addition to getopt() options.
 * This works a lot like GNU's getopt_long(). The last option in
 * longopts must be all zeros, marking the end of the array. The
 * longindex argument may be NULL.
 */
int optparse_long(struct optparse *options,
                  const struct optparse_long *longopts,
                  int *longindex);


/**
 * Used for stepping over non-option arguments.
 * @return the next non-option argument, or NULL for no more arguments
 *
 * Argument parsing can continue with optparse() after using this
 * function. That would be used to parse the options for the
 * subcommand returned by optparse_arg(). This function allows you to
 * ignore the value of optind.
 */
char *optparse_arg(struct optparse *options);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* OPTPARSE_H */