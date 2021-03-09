# Examples

## [`getting_started`](getting_started)

This example connects the output of one `Constant` component (value
3.0) with the input of an `FMU` component (`gain.fmu`), and runs the
simulation sequentially from time 0.0 to time 1.0 with step size
0.001.


## [`connections`](connections)

The `connections` example contains 3 FMUS:
- `Sum 1`  (`vectorSum.fmu`),
- `Sinus 1` (`sinusGenerator.fmu`), and
- `Gain 1` (`gain.fmu`).

The FMUs are connected via the following connections:
- `Sinus 1.sinus_out` to `Gain 1.real_in`
- `Gain 1.real_out[1:3]` to `Sum 1.v_1[1:3}`

Additionally, the (vector-)input `Sum 1.v_2` has a default value `1.0
2.0 3.0`, the step-size of `Sinus 1` is set to 0.05, and the
connection from `Sinus 1.sinus_out` to `Gain 1.real_in` is marked as
`DecoupleIfNeeded`, telling OpenMCx to extrapolate this connection, if
needed.

The `DefaultExperiment` is set up with an end time of 10.0.


## [`parameters`](parameters)

The `parameters` example defines one FMU (`sinusGenerator.fmu`) with the parameters
- `sin.amplitude`
- `sin.freqHz`
- `sin.phase`
- `sin.offset`
- `sin.startTime`
It also sets the value of parameter `sin.amplitude` to 13.0. This is
defined in _ParameterBindings_.

The `DefaultExperiment` is set up with an end time of 1.0.


## [`units`](units)

The `units` example defines custom units in the _Units_ section:
- `m` as 1`m`
- `cm` as 0.01`m`

The components in the model are:
- `Constant 1`
- `FMU 1` (`vectorSum.fmu`)

The output `Constant 1.Output` has a value of 3.0`m`. This output is
connected to all elements of the input vector `Fmu 1.v_1[1:3]`, which
is in `cm`. OpenMCx automatically converts between the units of the
output the corresponding input.

The _DefaultExperiment_ defines sequential calculation, and end time 0.02.


## [`vector_ports`](vector_ports)

The `vector_ports` example contains one FMU (`vectorSum.fmu`).
This FMU defines the vectors `v_1` and `v_2`, with of 3 elements each, as inputs, and the vector `b`, with 3 elements, as its output.
The output `b` is the element-wise addition of vectors `v_1` and `v_2`.
