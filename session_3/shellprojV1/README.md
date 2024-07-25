# program overview
the program simulates the shell but in a simple way and performs some tasks as pwd , cp , help , echo,exit, mv 
this program is at its beginning so there will be more modifications & versions

## Compilation command 
```
gcc main.c functions.c -o myShell

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
cp : copy a file given (1st argument) into the other file (2nd argument)
mv : move file to another directory
exit : terminates the shell
engez mafesh w2t lel tafser $> mv file.text test/
creating target file:: File exists
engez mafesh w2t lel tafser $> echo bassel mahmoud
bassel mahmoud 
engez mafesh w2t lel tafser $> exit
SALAM YA NIGM :(
```
## SUB commands 
### CP : -a
this sub-command is used if you want to append 2 files together in one target file
``` 
cp -a (source file path) (target file path)
```
#### example 
```
cp -a source.txt target.txt
```
here the content inside  ( source.txt ) is appended with the ( target.txt ) and saved inside target.txt
### MV : -f 
this sub-command is used to force overwrite the target file if it exists with  the same name of source file 
```
mv -f ( source file path )  ( target file path )
```

#### example 
```
mv -f source.txt target.txt
```
source.txt is moved to target file and force overwrite the target.txt if it exists with the same name  
