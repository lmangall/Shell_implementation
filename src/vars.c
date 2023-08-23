#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../include/node.h"
#include "../include/shell.h"
#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include "../include/vars.h"


// void init_vars(void);
// this function is called in main.c
// it takes all the variables from the environment and then copies them 
// into the variables array that is defined in variables.h
// after that it prints them all out

void print_vars(void)
{
	int i;

	i = 0;
	while (vars_container[i].name[0] != '\0')
	{
		printf("name: %s\n", vars_container[i].name);
		printf("value: %s\n", vars_container[i].value);
		i++;
	}
}

void init_vars(void)
{
	extern char **environ;
	int i;
	int j;
	int equal_sign;

	i = 0;
	while (environ[i] != NULL)
	{
		equal_sign = find_equal_sign(environ[i]);
		if (equal_sign == -1)
			return ;
		j = 0;
		while (j < equal_sign)
		{
			vars_container[i].name[j] = environ[i][j];
			j++;
		}
		vars_container[i].name[j] = '\0';
		j = 0;
		while (environ[i][equal_sign + 1] != '\0')
		{
			vars_container[i].value[j] = environ[i][equal_sign + 1];
			j++;
			equal_sign++;
		}
		vars_container[i].value[j] = '\0';
		i++;
	}
	vars_container[i].name[0] = '\0';
	vars_container[i].value[0] = '\0';
}


// set_vars takes a name and a value and sets the variable with that name to that value
// it adds it to the vars_container array if it doesn't exist
// it replaces the value if it does exist
// it returns 0 if it was successful and -1 if it failed
int set_vars(char *name, char *value)
{
	int i;

	i = 0;
	while (vars_container[i].name[0] != '\0')
	{
		if (strcmp(vars_container[i].name, name) == 0)
		{
			strcpy(vars_container[i].value, value);
			return (0);
		}
		i++;
	}
	if (i == MAX_VARS)
		return (-1);
	strcpy(vars_container[i].name, name);
	strcpy(vars_container[i].value, value);
	return (0);
}

// unset_vars takes a name and removes the variable with that name from the vars_container array
// it returns 0 if it was successful and -1 if it failed
int unset_vars(char *name)
{
	int i;
	int j;

	i = 0;
	while (vars_container[i].name[0] != '\0')
	{
		if (strcmp(vars_container[i].name, name) == 0)
		{
			j = i;
			while (vars_container[j].name[0] != '\0')
			{
				strcpy(vars_container[j].name, vars_container[j + 1].name);
				strcpy(vars_container[j].value, vars_container[j + 1].value);
				j++;
			}
			return (0);
		}
		i++;
	}
	return (-1);
}

// get_vars_value takes a name and returns the value of the variable with that name
// it returns NULL if it failed
char *get_vars_value(char *name)
{
	int i;

	i = 0;
	while (vars_container[i].name[0] != '\0')
	{
		if (strcmp(vars_container[i].name, name) == 0)
			return (vars_container[i].value);
		i++;
	}
	return (NULL);
}

int find_equal_sign(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

