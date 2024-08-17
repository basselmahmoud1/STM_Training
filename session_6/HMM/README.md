# Heap Memory Manager (HMM)

## Project Overview

This project implements a custom heap memory manager using a static array to simulate the heap. It uses a doubly linked list to manage free memory blocks and handle dynamic memory allocation and deallocation, similar to the `malloc` and `free` functions in the C standard library. The project also includes a custom implementation of the `HmmAlloc` and `HmmFree` functions.

### Features

- **Custom Memory Allocation (`HmmAlloc`)**: Allocates memory from a static array, managing free and used blocks using a doubly linked list.
- **Custom Memory Deallocation (`HmmFree`)**: Frees allocated memory and coalesces adjacent free blocks to minimize fragmentation.
- **Efficient Memory Management**: The manager tracks only the Free blocks, reducing overhead.
- **Makefile Included**: Easily compile the project using the provided Makefile.

## File Structure

- `HMM.h`: Header file containing the definitions and declarations of the HMM functions.
- `HMM.c`: Source file implementing the HMM functions.
- `linkedList.h`: Header file containing the definitions for the doubly linked list used to manage memory blocks.
- `linkedList.c`: Source file implementing the linked list operations.
- `main.c`: A test program that demonstrates the usage of the HMM functions.
- `test.c` : Another test for the program .
- `Makefile`: A makefile to build the project.

## Compilation

To compile the project, simply run:

```bash
make
```
This will compile all source files and generate the exe HMM.

## Running 
you can run the program using
```bash
./HMM (arrgument of function)
```
## Testing 

You can test the code using main.c or using test.c
as test.c allocate random memory size and Free random locations 
### test.c
to use test.c you must change the make file content by removing main.c and replaceing test.c




