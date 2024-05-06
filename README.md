# brain(fuck)
## What it does
This is a very simple brainfuck compiler that compiles brainfuck to nasm or binary.
## Building
Simply run
```
make
```
## Usage
```
./brain SRC [options]
```
Note that you must specify at least one option.
### Options
```
  -o FILENAME Output the result of compilation as a binary executable
  -a FILENAME Output the result of compilation as x86 assembly
  -v          Outputs the current version
  -h          Displays the manual page
```
## Cleanup
```
make clean
```
