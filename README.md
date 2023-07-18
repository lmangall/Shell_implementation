# minishell

### TO DO
- [ ] barebone working code
- [ ] Write tests before code ?
- [ ] have a testcase on the main 
- [ ] Checkbox 
- [ ] Checkbox 
- [ ] Checkbox 
- [ ] Checkbox 
- [ ] Checkbox 
- [ ] Checkbox 
- [ ] Checkbox 
- [ ] Checkbox 

----


### Ressources, informations and guide:
- [Let's Build a Linux Shell - Devgenius Part I](https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501)
- [Minishell](https://minishell.simple.ink/)
- [42cursus Minishell](https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6)
- [Miro Board: Minishell](https://miro.com/app/board/uXjVPqvBPlk=/?share_link_id=419876004646)
- [Minishell Documentation](https://harm-smits.github.io/42docs/projects/minishell)
- [How Bash Works](https://betterprogramming.pub/how-bash-works-8424becc12f3)
- [Tutoriels - Mini Système](https://chrtophe.developpez.com/tutoriels/minisysteme/#L1-1)
- - [Bash reference manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Bash Cookbook](https://theswissbay.ch/pdf/Gentoomen%20Library/Programming/Bash/O%27Reilly%20bash%20CookBook.pdf)
https://github.com/maiadegraaf/minishell
https://github.com/appinha/42cursus-03-minishell
fr: https://github.com/iciamyplant/Minishell
fr: https://github.com/LucieLeBriquer/minishell∏

- [chdir function](https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/)
- 
- [Bash cookbook](https://theswissbay.ch/pdf/Gentoomen%20Library/Programming/Bash/O%27Reilly%20bash%20CookBook.pdf)
- []()
- []()
- []()
- 
- [GFG pipe System call ](https://www.geeksforgeeks.org/pipe-system-call/?ref=rp)
- [GFG Wait System Call in C](https://www.geeksforgeeks.org/wait-system-call-c/?ref=rp)
- [GFG fork in C](https://www.geeksforgeeks.org/fork-system-call/?ref=rp)
- [Making your own Linux Shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)
- []()

### Google sheets for testing:
https://docs.google.com/spreadsheets/u/0/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/htmlview?lsrp=1#gid=0
https://docs.google.com/spreadsheets/d/1TDwyd-S0WBAXehgkrKQtBJ6zquQ4p6k7JfE5g3jICNA/edit#gid=0


### Carlo docker to have ubuntu (in order to have valgrind etc...)
https://gist.github.com/CarloCattano/73482a9e846e27165e85dcf32cda91ad

### Carlo graph for doxygen comments:
https://gist.github.com/CarloCattano/1f1db247c4eb8477a365e29eaf12aaf1


### Advices :
*Advice from Martin* 
- avoid *merge conflict* 
- switch on a setting on the repo that doesn't allow anybody to push straight to main -> it has to be pushed to a branch before
- Eventually a second setting : when one person pushes the code HAS TO be reviewed by the other person
- have multiples folders
- keep functions small and clear

*Advice from Guillaume and Jules:*
- Be careful with forks commands that kills a program after execution (a.i 'ls'). It needs to be executed as a child (not a parent) in order not to kill the whole minishell.
- Parent/child: no need to use wait, the exec of one cmd will wait the output of the first "by itself"





### Overal operation

*lexer -> parser ( -> expander ) -> executor *

Lexer = Lexical Analyzer

The parser scans input and breaks it down to tokens. A token consists of one or more characters (letters, digits, symbols), and represents a single unit of input. For example, a token can be a variable name, a keyword, a number, or an arithmetic operator.
The parser takes these tokens, groups them together, and creates a special structure we call the Abstract Syntax Tree, or AST. The parser takes the AST and passes it to the executor, which reads the AST and executes the parsed command.
Most shells implement a structure known as the *symbol table*, which the shell uses to store information about variables, along with their values and attributes.

PS1 and PS2 are environment variables used to customize the prompt string and secondary prompt string.
 - PS1 (Primary Prompt String): is displayed when the shell is ready to accept user input. It typically includes information like the username, hostname, current directory, or any other desired details.
 - PS2 (Secondary Prompt String): is displayed when the shell expects more input to complete a command that spans multiple lines. It is often referred to as the continuation prompt. By default, the secondary prompt is displayed as three dots (...).





## Functions allowed to use

| Category               | Functions                                                                                                             |
|------------------------|-----------------------------------------------------------------------------------------------------------------------|
| Input/Output           | readline, printf, write                                                                                              |
| Memory Management      | malloc, free                                                                                                          |
| History and Line Editing| rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history                                          |
| File and Directory Operations | access, open, read, close, stat, lstat, fstat, unlink, opendir, readdir, closedir                                  |
| Process Control        | fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit                              |
| File Descriptor Manipulation | dup, dup2                                                                                                         |
| Pipes                  | pipe                                                                                                                  |
| Current Working Directory | getcwd, chdir                                                                                                        |
| Error Handling         | strerror, perror                                                                                                      |
| Terminal Handling      | isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |



| Function     | Description                                                                                               |
|--------------|-----------------------------------------------------------------------------------------------------------|
| `readline`   | Reads a line of input from the user, providing line editing and history capabilities.                     |
| `rl_clear_history` | Clears the history list maintained by the readline library.                                          |
| `rl_on_new_line` | Informs readline that the prompt has been printed, and the next input should be read.                   |
| `rl_replace_line` | Replaces the current input line with a new line.                                                      |
| `rl_redisplay` | Updates the display to reflect changes made by other readline functions.                                |
| `add_history` | Adds a line to the history list.                                                                         |
| `printf`     | Prints formatted output to the standard output stream.                                                  |
| `malloc`     | Allocates a block of memory on the heap.                                                                 |
| `free`       | Deallocates a block of memory previously allocated by `malloc`.                                         |
| `write`      | Writes data to a file descriptor, typically used for writing to the standard output or a file.           |
| `access`     | Checks the accessibility of a file or directory.                                                        |
| `open`       | Opens a file or device.                                                                                  |
| `read`       | Reads data from a file descriptor into a buffer.                                                         |
| `close`      | Closes a file descriptor.                                                                                |
| `fork`       | Creates a new process by duplicating the existing process.                                               |
| `wait`, `waitpid`, `wait3`, `wait4` | Functions to wait for the child process to terminate and retrieve its termination status.          |
| `signal`     | Sets a signal handler for a specific signal.                                                              |
| `sigaction`  | Specifies the action to be taken for a specific signal.                                                   |
| `sigemptyset`, `sigaddset` | Manipulate signal sets to specify which signals are blocked or unblocked.                          |
| `kill`       | Sends a signal to a process or a group of processes.                                                      |
| `exit`       | Terminates the calling process and returns an exit status to the parent process.                         |
| `getcwd`     | Retrieves the current working directory.                                                                  |
| `chdir`      | Changes the current working directory.                                                                    |
| `stat`, `lstat`, `fstat` | Retrieve file or file system status.                                                               |
| `unlink`     | Deletes a name from the file system.                                                                      |
| `execve`     | Replaces the current process with a new process specified by the provided executable file.                |
| `dup`, `dup2` | Duplicates a file descriptor.                                                                         |
| `pipe`       | Creates a pipe, which is a unidirectional data channel.                                                   |
| `opendir`, `readdir`, `closedir` | Functions for working with directories.                                                          |
| `strerror`   | Returns a string describing the error code passed to it.                                                  |
| `perror`     | Prints a system error message to the standard error stream.                                              |
| `isatty`     | Checks if a file descriptor refers to a terminal.                                                        |
| `ttyname`    | Returns the name of the terminal associated with a file descriptor.                                      |
| `ttyslot`    | Returns the slot number of the current user's terminal.                                                  |
| `ioctl`      | Performs I/O control operations on devices.                                                              |
| `getenv`     | Retrieves the value of an environment variable.                                                          |
| `tcsetattr`, `tcgetattr` | Functions for manipulating terminal attributes.                                                      |
| `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs` | Functions for interacting with the terminal database and performing terminal-related operations. |




## Chat gpt blob

1. User Input and Parsing: The shell interacts with the user by accepting input through the command line. You need to design a mechanism to read user input and parse it into individual commands and arguments. Common parsing techniques include splitting the input into tokens or using regular expressions.

2. Command Execution: Once you have parsed the user input, you need to execute the corresponding command. This involves searching for the command in the command table and executing the associated functionality. You can use system calls or library functions to execute commands or external programs.

3. Built-in Commands: Shells often provide built-in commands that are implemented directly within the shell itself. Examples include "cd" for changing directories or "echo" for printing text. These commands are usually handled separately from external commands and may require special treatment.

4. Environmental Variables: Shells allow users to set and manipulate environmental variables, which are used to store information such as system paths, user preferences, or temporary data. You'll need to implement mechanisms for managing environmental variables, including setting, retrieving, and modifying their values.

5. Input/Output Redirection: Shells support input/output redirection to allow users to control the flow of data. This includes redirecting the input of a command from a file or sending the output of a command to a file. You'll need to handle the syntax and perform the necessary file operations.

6. Pipelines: Shells often support pipelines, which enable chaining multiple commands together by connecting the output of one command to the input of another. Implementing pipelines involves coordinating the execution of multiple commands and handling the passing of data between them.

7. Shell Scripting: A powerful feature of shells is the ability to write shell scripts. Shell scripts are files containing sequences of commands that can be executed as a single unit. You may consider adding support for executing shell scripts in your shell implementation.

8. Error Handling and Signal Handling: Robust shells handle errors and signals appropriately. You should handle errors gracefully, provide meaningful error messages to the user, and handle signals like Ctrl+C (interrupt signal) or Ctrl+Z (suspend signal) appropriately.



## Example

```shell
ls | grep "txt" | sort | head -n5
```

|   STEP   | COMMAND |  ARGUMENTS | INPUT_FILE | OUTPUT_FILE |
|----------|---------|------------|------------|-------------|
|     00   |   ls    |    NULL    |    NULL    |    NULL     |
|     01   |  grep   |   "txt"    |    NULL    |    NULL     |
|     02   |  sort   |    NULL    |    NULL    |    NULL     |
|     03   |  head   |    -n5     |    NULL    |    NULL     |



---

```shell
cat input.txt | grep "error" > output.txt | wc -l
```

|   STEP   | COMMAND |  ARGUMENTS | INPUT_FILE | OUTPUT_FILE |
|----------|---------|------------|------------|-------------|
|     00   |   cat   |    NULL    | input.txt  |    NULL     |
|     01   |  grep   |  "error"   |    NULL    | output.txt  |
|     02   |   wc    |    -l      |    NULL    |    NULL     |








