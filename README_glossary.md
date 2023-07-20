# minishell
1. Prompt: The text displayed to indicate that the shell is ready to receive user input.

2. Command: A program or built-in functionality that the shell can execute.

3. Argument: Additional information provided to a command that modifies its behavior or specifies inputs.

4. Shell variables: Variables that store values used within the shell environment.

5. Environment variables: Global variables that store system information and configuration.

6. Built-in commands: Commands that are implemented within the shell itself, rather than being external programs.

7. Path: A list of directories where the shell looks for executable programs.

8. Background execution: Running a command asynchronously, allowing the shell to continue accepting input and executing other commands.

9. Job control: The ability to manage and manipulate multiple running processes within the shell.

10. Wildcards: Special characters that represent patterns used for matching filenames or commands.

11. Subshell: A separate instance of the shell, typically created to execute commands within a script or a command substitution.

12. Signal: A software interrupt delivered to a process, used for various purposes such as terminating or suspending a process.

13. Pipeline: Connecting multiple commands together, where the output of one command serves as the input of the next.

14. Background/Foreground process: Background processes are executed independently, while foreground processes require user interaction and suspend the shell.

15. Exit status: A value returned by a command that indicates the success or failure of its execution.

1. Shell script: A file containing a sequence of shell commands and instructions that can be executed by the shell.

2. Aliases: Shortcuts or alternate names for commands or command sequences.

3. Job control signals: Signals used to manage and control running processes, such as sending them to the background or bringing them to the foreground.

4. Command substitution: A feature that allows the output of a command to be used as part of another command or assigned to a variable.

5. Interactive mode: A mode in which the shell accepts input directly from the user and provides immediate feedback.

6. Batch mode: A mode in which the shell reads commands from a file or a script and executes them without user interaction.

7. Shell options: Settings that control the behavior and features of the shell, such as enabling or disabling specific functionalities.

8. Signal handling: The process of defining how the shell should respond to various signals received from the operating system or user.

9. Standard input (stdin): The default input source for a command, typically connected to the keyboard.

10. Standard output (stdout): The default output destination for a command, typically connected to the terminal.

11. Standard error (stderr): The default error output destination for a command, typically connected to the terminal.

12. Background/Foreground job management: Controlling and manipulating background and foreground processes, including starting, stopping, and managing their execution.

13. Command history: A feature that allows the shell to store a list of previously executed commands, typically accessible through keyboard shortcuts or command history functions.

14. Shell initialization files: Files read and executed by the shell at startup, allowing the customization of shell settings and defining environment variables.

15. Command-line editing: Techniques and shortcuts for editing and manipulating the command line input before executing it.

16. Termination and exit: The process of ending the shell's execution, either by user command or upon completion of all tasks.

17. Quoting and escaping: Techniques for specifying literal values, preventing interpretation of special characters, and preserving whitespace within commands and arguments.

18. Job scheduling: The ability to schedule commands or scripts to run at specified times or intervals.

19. File globbing: Pattern matching technique used to expand wildcard characters in filenames.

20. Input/output redirection: The process of changing the default sources or destinations of input and output for a command.


system call






### Logical AND (&&) operator
Syntax: command1 && command2
Meaning: Execute command1 and if it succeeds (returns an exit status of 0), then execute command2.
Behavior:
 - If command1 succeeds (returns exit status 0), command2 is executed.
 - If command1 fails (returns a non-zero exit status), command2 is not executed.

 Example:
Only remove the file if it exists and the removal is successful
rm file.txt && echo "File removed"

### Logical OR (||) operator
 Syntax: command1 || command2
Meaning: Execute command1 and if it fails (returns a non-zero exit status), then execute command2.
Behavior:
 - If command1 succeeds (returns exit status 0), command2 is not executed.
  - If command1 fails (returns a non-zero exit status), command2 is executed.

 Example:
If the file does not exist, create it
touch file.txt || echo "File created"
