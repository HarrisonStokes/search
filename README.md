# Where Are You (WAY)

## TODO:
    1. Add more rigorous testing.
    2. Implement following features:
         * -q, to make the program return true or false when a pattern is found.
         * -d, to search files in a directory.
         * -R, to search a directory and all its subdirectory files.

## How to use
`./way [patterns] -i [source files] -[flags] -o [output files]`


### Flags
Every destination file must be preceeded with a "-o"
* -q : doesn't print to screen (To be expounded upon later).
* -c : highlights character sequence.
* -i : case insensitivity.
* -R : recurse search (have to use the pathway option).
* -d : searches through a directory instead.
