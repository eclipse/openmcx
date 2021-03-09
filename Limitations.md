# SSP Limitations
OpenMCx introduces a few limitations on the SSP standard used for defining input files:

- `Enumerations` are not supported
- `Transformations` are not supported
    - `LinearTransformation`
    - `BooleanMappingTransformation`
    - `IntegerMappingTransformation`
    - `EnumerationMappingTransformation`
- Random system hierarchies are not supported (see next point)
- The maximum allowed hierarchy level is 1, where all components at the top level __MUST__ have a
  `CoSimulation` implementation.
- `SignalDictionaries` are not supported
- `SignalDictionaryReferences` are not supported
- Connector kinds `inout` and `calculatedParameter` are not supported
- Parameter value resolution based on hierarchical names is not supported
    - Only `ParameterBindings` at the element level are taken into account
- `ParameterValues` __MUST__ be provided inline and not via an `.ssv` file
- Parameter values are applied __ONLY TO__ parameter connectors defined in the system description
- `ParameterMappings` are not supported
- Parameter connections and connections between system connectors are not supported
- `UnitConversionSuppression` is not supported
- Arbitrary URIs are not supported (e.g. as the `source` of a component).
  Only relative and absolute paths are supported
- Implicit connector type lookup based on the underlying component (e.g. FMU) is not supported.
- Parameter values must have the same unit (or none) as the respective connector