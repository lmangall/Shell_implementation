#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../include/main.h"
#include "../lib/libft/src/libft.h"

//we can use a preprocessor # define to define the error messages
// code and message can just be copied from errno.h for accuracy

// # define ENOMEM "Cannot allocate memory\n"
// # define ENODATA "No message available on STREAM\n"

// # define ENODATA "No message available on STREAM\n"
// # define ENODATA "No message available on STREAM\n"

void	exit_print(char *msg)
{
	ft_putstr_fd("Error:\n", 2);
	ft_putendl_fd(msg, 2);
	/*
	if (ft_strcmp(msg, "correct execution") != 0)
	{
		ft_putstr_fd("Error:\n", 2);
		ft_putendl_fd(msg, 2);
	}
	if (ft_strcmp(msg, "Nothing to sort") == 0 || ft_strcmp(msg,
			"Duplicate among the arguments") == 0)
		exit(1);
	if (ft_strcmp(msg, "sorted") == 0)
	{
		free_stack(*stack_a);
		exit(1);
	}
	if (stack_a != NULL)
		free_stack(*stack_a);
	*/
	exit(1);
}