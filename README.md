# Where Are You (WAY)


## TODO:
1. Refactor
	* Focusing on modularality, portability, and redudancy
2. Fix config support
3. Make sure name issues are fixed

## Operations

### Execution
#### General
./way [src1 ... srcN] -FLAGS  [-o dest1 ... -o destN]
#### Starting from a pathway
./way [starting path] -R(FLAGS) [-o dest1 ... -o destN]



### Flags
Every destination file must be preceeded with a "-o"
* -q : doesn't print to screen (To be expounded upon later).
* -c : highlights character sequence.
* -i : case insensitivity.
* -R : recurse search (have to use the pathway option).
* -d : searches through a directory instead.
