# captest

## Description
`captest` is a simple C++-based program that executes a binary using a given [kernel file capabilities](https://man7.org/linux/man-pages/man7/capabilities.7.html) set, that is provided in a [human-readable form](https://man7.org/linux/man-pages/man3/cap_from_text.3.html) together with the action list and operator flags (see the [Textual Representation](https://man7.org/linux/man-pages/man3/cap_from_text.3.html#TEXTUAL_REPRESENTATION) section of the reference).

The original file capabilities are saved before the execution, new ones are temporarily assigned to the file, the binary is executed and the original caps are brought back.

## Usage and examples

```
# ./captest <path to the binary> <human-readable capabilities>
```

For example:
```
# ./captest /bin/ls cap_dac_override=ep
```
