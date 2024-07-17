# compilation commands 
```
gcc -E elfparser.c 1> elfparser.i
gcc -S elfparser.i
gcc -c elfparser.s
gcc elfparser.o -o app
```
## output example 

for the elfheader of app file (exeutable file)

```
Magic :   7f  45  4c  46  02  01  01  00  00  00  00  00  00  00  00  00
Class :                 ELF64
Data :          Two's complement, littel-endian
Version :               1 (Current version)
OS/ABI :                UNIX System V ABI
ABI Version :            0 
Type :          DYN (A shared object file)
Machine :               AMD x86-64
Version :               current version (0x3e)
Entry point address :           0x00001100
Start of program headers :              40
Start of section headers :              14200
Flags :                  0x00
Size of this header :           64  (in bytes)
Size of program headers :               56  (in bytes)
Number of program headers :             13
  Size of section headers :             64  (in bytes)
Number of section headers :             31
  Section header string table index :           30

```
