#ifndef BACKEND_H
#define BACKEND_H
#include "node.h"
char	*ft_strjoin(char const *str1, char const *str2);

/**
 * @brief Searches for the executable file of a given command in the directories listed in the $PATH variable.
 *
 * The search_path() function takes the name of a command and searches for its executable file in the directories
 * listed in the $PATH environment variable. The $PATH variable contains a comma-separated list of directories,
 * such as /bin:/usr/bin. For each directory in the $PATH, the function creates a full pathname by appending the
 * command name to the directory name and then calls stat() to check if a file exists with the given pathname
 * (for simplicity, the function doesn't check whether the file is actually executable or whether the user has
 * enough permissions to execute it).
 *
 * @param file The name of the command to search for.
 *
 * @return The full pathname of the command's executable file if found; otherwise, returns NULL. If the command is
 *         not found in any of the directories in the $PATH, the function returns NULL, indicating that the user
 *         might have typed an invalid command name.
 */
char* search_path(char* file);
/**
 * @brief Executes a command by calling execv().
 *
 * The do_exec_cmd() function executes a command by calling execv() to replace the current process image with the new
 * command executable. If the command name contains any slash characters, it is treated as a pathname, and the function
 * directly calls execv() with the given command and arguments. Otherwise, the function tries to locate the command
 * by calling search_path(), which should return the full pathname of the command executable that will be passed on
 * to execv().
 *
 * @param argc The number of command-line arguments (including the command name itself).
 * @param argv An array of pointers to strings representing the command-line arguments, where argv[0] is the command
 *             name itself, and the rest are the arguments.
 *
 * @return If the function successfully executes the command using execv(), it will not return because the current
 *         process image is replaced with the new command image. If there is an error in locating or executing the
 *         command, the function may return -1, and errno will be set appropriately.
 */
int do_exec_cmd(int argc, char** argv);

/**
 * @brief Executes a simple command from the Abstract Syntax Tree (AST).
 *
 * The do_simple_command() function is the main function in our executor. It takes the command's Abstract Syntax Tree
 * (AST) represented by the `node` parameter and converts it into an argument list (`argv`) suitable for executing
 * the command. The zeroth argument, argv[0], contains the name of the command we want to execute. The function then
 * executes the command by calling the appropriate execution function based on the command type and arguments.
 *
 * @param node A pointer to the root node of the Abstract Syntax Tree (AST) representing the simple command.
 *
 * @return If the function successfully executes the command, it may return the return value of the executed command
 *         or any specific success value. If there is an error in executing the command, the function may return an
 *         appropriate error code, and errno will be set accordingly.
 */
int do_simple_command(struct node_s* node);
#endif