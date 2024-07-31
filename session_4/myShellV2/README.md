# Simple Shell

This is a simple shell implementation in C that supports basic built-in commands and external commands. The shell can execute commands like `cd`, `echo`, `exit`, `help`, `mv`, `pwd`, `type`, and `envir`.

## Features

- **Built-in commands**:
  - `cd`: Change directory.
  - `mycp`: Copy files.
  - `echo`: Print text to the terminal.
  - `exit`: Exit the shell.
  - `help`: Display help for built-in commands.
  - `mymv`: Move files.
  - `mypwd`: Print the current working directory.
  - `type`: Display the type of command (internal, external, or unsupported).
  - `envir`: Display environment variables.
  - `myps` : Display last 10 process done by shell.
- **External commands**: The shell can execute external commands found in the system's `PATH`.
- **Environment variables**: the shell can dereference the environment variable and return its value.
  ```sh
  Engez Mafesh W2t Lel Tafser $> $PATH
    ('print the PATH in your device')
  ```
  <img src ="https://github.com/user-attachments/assets/e2310d5b-b7db-4abf-bb89-0fa3feee08a3"  width = 700 > 
- **Process History**: the shell can record and print the last 10 processes done by it using `myps` command.
 
  <img src ="https://github.com/user-attachments/assets/39cbc420-8492-48b7-b411-366a66e5c80e"  width = 700 > 
- **Cool Colored promote message** 
   <img src ="https://github.com/user-attachments/assets/9b4ead89-6c89-41fc-ace0-78464955593c"  width = 700 > 
  

## How It Works

The shell reads input from the user, tokenizes the input to identify the command and its arguments, and then executes the command. Built-in commands are handled directly by the shell, while external commands are executed from `PATH`.

## Project Structure

- `main.c`: The entry point of the shell. Handles the main loop of reading and executing commands.
- `builtin.c`: Contains the implementation of built-in commands.
- `builtin.h`: Header file for `builtin.c`.
- `functions.c`: Contains helper functions for reading user input, tokenizing commands, and checking command types.
- `functions.h`: Header file for `functions.c`.
- `external.c` : Contain the implementations of function that make process to execute the external command.
- `external.h`: Header file for `external.c`.
## Compliation

1. **Cloning the Repository** : `git clone https://github.com/basselmahmoud1/STM_Training.git `
    `cd session_4\myShellV2`  
2. **Compile the project**:

    ```sh
    gcc -o myShellV2 main.c builtin.c functions.c external.c
    ```

3. **Run the shell**:

    ```sh
    ./myShellV2
    ```

4. **Use the shell**:

    You can type commands at the shell prompt. For example:

    ```sh
    Engez Mafesh W2t Lel Tafser $> cd /path/to/directory
    Engez Mafesh W2t Lel Tafser $> echo "Hello, world!"
    Engez Mafesh W2t Lel Tafser $> pwd
    Engez Mafesh W2t Lel Tafser $> type ls
    ```

## Implementation Details

### Command Tokenization

Commands entered by the user are tokenized using the `strtok` function. The command and its arguments are stored in an array of strings.

### Built-in Commands

Built-in commands are implemented in the `builtin.c` file. Each built-in command is a function that takes the command's arguments as input.

### External Commands

External commands are checked against the system's `PATH` to determine if they are executable. The `type` function identifies whether a command is internal, external, or unsupported.

## Further Upgrades

This project is designed to be extendable and can be enhanced with various additional features. Below are some suggested upgrades to consider:

### 1. Adding Piping
**Piping** allows the output of one command to be used as the input for another command, enhancing the flexibility and power of your shell.

#### Example:
```sh
cat file.txt | grep "search_term"
```
### 2. Implementing Redirection
**Redirection** allows the user to redirect the standard input/output of commands to/from files.

#### Example:
```sh
ls > output.txt
cat < input.txt
```
### 3. Job Control
Implement job control features such as running processes in the background, bringing them to the foreground, and listing running jobs.

#### Example:
```sh
sleep 100 &
jobs
fg %1
```
