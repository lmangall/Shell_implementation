/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/15 16:56:34 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/pipe.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec_cmd(char **argv, t_data *data)
{
	char	*path;
	char	**custom_env;

	custom_env = convert_vc_to_envp(data);
	data->envp_arr = custom_env;
	if (ft_strchr(argv[0], '/'))
	{
		handle_absolute_path(argv, custom_env);
	}
	else
	{
		path = search_path(argv[0], data);
		if (!path)
			return (0);
		data->path = path;
		execve(path, argv, custom_env);
	}
	return (0);
}

void    update_status_and_cleanup(int status, t_data *data)
{
    if (WIFEXITED(status))
        set_var(data, "?", ft_itoa(WEXITSTATUS(status)));
    else if (WIFSIGNALED(status))
        set_var(data, "?", ft_itoa(WTERMSIG(status) + 128));
}

void    simple_or_advanced(char **tokens, t_data *data)
{
    int             status;
    struct s_node   *cmd;

    status = 0;
    if (get_operator(tokens) != NONE)
    {
        cmd = parse_advanced_command(tokens);
        if (fork() == 0)
        {

            exec_pipe_redir(cmd, data);

        }
        waitpid(-1, &status, 0);
        // printf("\033[1;36mTHIS IS IN THE COMPLEX COMPLEX COMPLEX COMMAND\n\033[0m");
        // printf("\033[1;33mstatus is %d\n\033[0m", status);
        // printf("\033[1;32mWEXITSTATUS IS %d\n\033[0m", WEXITSTATUS(status));
        // printf("\033[1;31mWIFSIGNALED IS %d\n\033[0m", WIFSIGNALED(status));
        // printf("\033[1;31mWTERMSIG IS %d\n\033[0m", WTERMSIG(status));
        update_status_and_cleanup(status, data);

        free_node_tree_recursive(cmd);
    }
    else
    {
        if (fork() == 0)
        {
            cmd = parse_simple_command(tokens, data);
            exec_pipe_redir(cmd, data);
        }
        waitpid(-1, &status, 0);
        // printf("\033[1;36mTHIS IS IN THE SIMPLE COMMAND\n\033[0m");
        // printf("\033[1;33mstatus is %d\n\033[0m", status);
        // printf("\033[1;32mWEXITSTATUS IS %d\n\033[0m", WEXITSTATUS(status));
        // printf("\033[1;31mWIFSIGNALED IS %d\n\033[0m", WIFSIGNALED(status));
        // printf("\033[1;31mWTERMSIG IS %d\n\033[0m", WTERMSIG(status));
        update_status_and_cleanup(status, data);
    }

    
    free_string_array(data->tokens);

}
