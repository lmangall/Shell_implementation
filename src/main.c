/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/13 12:30:00 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../include/free.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/shell.h"
#include "../include/signals.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	t_data	data;

	(void)argc;
	(void)argv;
	data.paths = NULL;
	data.envp = NULL;
	// data = malloc(sizeof(t_data)); // Allocate memory for data
	// if (!data)
	// {
	// 	fprintf(stderr, "lsh: allocation error\n");
	// 	exit(EXIT_FAILURE);
	// }
	init_vars(&data, envp);
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
	status = 1;
	while (status)
	{
		line = readline(SHELL_PROMPT);     // what is returned is malloced and should be freed
		if (line == NULL)
			handle_ctrl_d(SIGQUIT);
		if (line[0] != '\0')
		{
			add_history(line);
			status = check_and_builtins(line, &data);
			if (status == 1)
				status = parse_and_execute(line, &data);
		}
	}
	return (EXIT_SUCCESS);
}

// write a command that frees the AST from the master node
static void	free_ast(struct node_type_master *master_node)
{
	int	i;

	i = 0;
	while (i < master_node->nbr_root_nodes)
	{
		free_node_tree(master_node->root_nodes[i]);
		i++;
	}
	free(master_node->root_nodes);
	free(master_node);
}

int	parse_and_execute(char *line, t_data *data)
{
	char					**tokens;
	int						status;
	struct node_type_master	*master_node;
	struct node_s			*cmd;

	tokens = lexer(line);
	free(line);
	status = 0;
	if (get_operator(tokens) != NONE)
	{
// have parse_advanced_command return smthing for execution, instead of executing straight away
		master_node = parse_advanced_command(tokens);
		// print_master(master_node);
		if (fork() == 0)
			exec_pipe_redir(master_node->root_nodes[0]);
		waitpid(-1, &status, 0);
		free_ast(master_node);
	}
	else
	{
		cmd = parse_simple_command(tokens);
		if (cmd->first_child->next_sibling != NULL)
			expansion_substitution(cmd->first_child->next_sibling, data);
		if (fork() == 0)
			exec_pipe_redir(cmd);
		waitpid(-1, &status, 0);
		// free_node(cmd);
	}
	// free(tokens);
	return (1);
}
