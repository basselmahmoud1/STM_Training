# program overview
the program simulates the shell but in a simple way and performs some tasks as pwd , cp , help , echo,exit, mv 
this program is at its beginning so there will be more modifications & versions

## Compilation command 
```
gcc main.c functions.o -o myShell

```
## output example
```
engez mafesh w2t lel tafser $> pwd
/home/bassel_mahmoud1/Desktop/STM_Training/session_3/shellprojV1
engez mafesh w2t lel tafser $> 
engez mafesh w2t lel tafser $> 
engez mafesh w2t lel tafser $> help
supported commands are :
pwd : prints the current working directory
echo : print back the string given
cp : copy a file given (1st argumment) into the other file (2nd argumment)
mv : move file to another directory
exit : terminates the shell
engez mafesh w2t lel tafser $> mv file.text test/
creating target file:: File exists
engez mafesh w2t lel tafser $> echo bassel mahmoud
bassel mahmoud 
engez mafesh w2t lel tafser $> exit
SALAM YA NIGM :(
```
