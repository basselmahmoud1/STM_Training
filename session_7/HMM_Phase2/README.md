# Heap Memory Manager (HMM)

## Project Overview

This project implements a custom heap memory manager using a real heap. It uses a doubly linked list to manage free memory blocks and handle dynamic memory allocation and deallocation, which is the same implementation of  `malloc` and `free` functions in the C standard library. The project also includes a custom implementation of the `HmmAlloc` and `HmmFree` functions.

### Features

- **Custom Memory Allocation (`HmmAlloc`)**: Allocates memory from a static array, managing free and used blocks using a doubly linked list.
- **Custom Memory Deallocation (`HmmFree`)**: Frees allocated memory and coalesces adjacent free blocks to minimize fragmentation.
- **Efficient Memory Management**: The manager tracks only the Free blocks, reducing overhead.
- **Reallocation of Memory (`realloc`)** : it can increase the size of the previously allocated block without changing its content.
- **Calloc(`Calloc`)** : it can allocate blocks of memory and initialize that block with `0` . 
- **Algorithm**: `First fit` is the used algorithm 

## File Structure

- `HMM.h`: Header file containing the definitions and declarations of the HMM functions.
- `HMM.c`: Source file implementing the HMM functions.
- `linkedList.h`: Header file containing the definitions for the doubly linked list used to manage memory blocks.
- `linkedList.c`: Source file implementing the linked list operations.
- `main.c`: A test program that demonstrates the usage of the HMM functions.
- `libhmm.so` : this is the shared lib file that can bu used to replace `malloc` , `free`,`calloc` and `realloc` .


## Compilation

To compile the project, simply run:

```bash
gcc -c -fPIC HMM.c linkedList.c
gcc -shared -o libhmm.so linkedList.o HMM.o

LD_PRELOAD=`realpath libhmm.so` (your application name)
```
This will compile all source files and generate the shared lib `libhmm.so` .

## Running 
you can run the program using
```bash
LD_PRELOAD=`realpath libhmm.so` (your application name)
```
## Testing 

You can test the code using `bash` or using `vim`

## Further improvements 
-The lib can't deal with application using threads as `gdb` it can support it in further versions 



