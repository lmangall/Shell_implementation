
static inline void free_argv(int argc, char **argv)
{
	if(!argc)
		return;
	while(argc--)
	free(argv[argc]);
}

// static void print_pipe_write_end(int pipe_fd)
// {
//     char buffer[1024];
//     ssize_t bytes_read;

//     while ((bytes_read = read(pipe_fd, buffer, sizeof(buffer))) > 0)
//     {
//         printf("\033[1;35m"); // Set the color to purple
//         fwrite(buffer, 1, bytes_read, stdout);
//         printf("\033[0m"); // Reset the color
//     }

//     if (bytes_read == -1)
//     {
//         perror("read");
//         exit(EXIT_FAILURE);
//     }
//     else if (bytes_read == 0)
//     {
//         fprintf(stderr, "Error: pipe_fd is not open or has been closed prematurely\n");
//         printf("void_pipe_write_end 0 bytes read\n");
// 		exit(EXIT_FAILURE);
//     }
// }

int	first_child(struct node_s *node, int pipe_fd[2])
{
write(2, "Y", 2);
write(2, "\n", 2);
	int PID;
	PID = 0;
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
	(void) pipe_fd;
	(void) node;
    PID = do_simple_command(node);
write(2, "X", 2);
write(2, "\n", 2);
	exit(EXIT_SUCCESS);
	return PID;
}

int	second_child(struct node_s *node, int pipe_fd[2])
{
	int PID;
	PID = 0;
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
	PID = do_simple_command(node);
	return PID;
	exit(EXIT_SUCCESS);

}

int execute_pipe_command(struct node_type_master *master_node)
{
    int pipe_fd[2];
    pid_t pid1, pid2;
    int status;
	// int pid3;
	// int pid4;
	
	// pid3 = 0;
	// pid4 = 0;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid1 == 0)
    {
		set_node_str(master_node->root_nodes[0]->first_child, "ls"); // !!!
        first_child(master_node->root_nodes[0], pipe_fd);
        exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid2 == 0)
    {
		set_node_str(master_node->root_nodes[2]->first_child, "wc");// !!!
       second_child(master_node->root_nodes[2], pipe_fd);
        exit(EXIT_SUCCESS);
    }

    // close(pipe_fd[0]);
    // close(pipe_fd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
	// waitpid(pid3, &status, 0);
	// waitpid(pid4, &status, 0);

    return WEXITSTATUS(status);
}


// a function that uses do_exec_cmd to execute a simple command
int do_simple_command(struct node_s *node)
{
	struct node_s *child = node->first_child;
	if(!child)
		return 0;

	int PID = 0;
	int argc = 0;
	long max_args = 255;
	char *argv[max_args+1];/* keep 1 for the terminating NULL arg */
	char *str;

	if(child)
	// while(child)
	{
		str = child->str;
		argv[argc] = malloc(strlen(str)+1);
		
	if(!argv[argc])
		{
			free_argv(argc, argv);
			return 0;
		}
printf("str: %s\n", str);
	strcpy(argv[argc], str);
		// if(argc >= max_args)
		// {
		// 	break;     //that doesn't work in an if statement
		// }

//commentend so we do one command without args
//if you uncomment be carefull checking that 
//there is no pointer to next_sibling pointing at wrong place or such...
		// child = child->next_sibling;///////causes problems
		argc++;
	}
		argv[argc] = NULL;

		
for (int i = 0; argv[i] != NULL; i++)
{
    printf("argv[%d]: %s\n", i, argv[i]);
}


		PID = do_exec_cmd(argv);
		free_argv(argc, argv);
		return PID;

}