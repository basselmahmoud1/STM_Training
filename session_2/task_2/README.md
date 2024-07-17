# compilation commands 
```
gcc -E elfparser.c 1> elfparser.i
gcc -S elfparser.i
gcc -c elfparser.s
gcc elfparser.o -o app
```
