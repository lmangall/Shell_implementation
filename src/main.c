/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/07/18 20:26:41 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef struct data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd;
	char	**cmd_path;
	char	**cmd_args;
	char	*path;
	int		pipe_status;
}	t_data;


static char	*get_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);

static void	fill_list(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->fd_in = -1;
	data->pid1 = -2;
	data->pid2 = -2;
	data->pipe_status = -2;
	data->fd_out = -1;
	data->path = get_path(envp);
	data->cmd_path = ft_split(data->path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	fill_list(&data, argc, argv, envp);
	if (argc != 5)
		error_args(data);
	data.fd_in = file_open(argv[1], IN, data);
	data.fd_out = file_open(argv[4], OUT, data);
	error_file(data);
	data.pipe_status = pipe(data.pipe_fd);
	error(data);
	data.pid1 = fork();
	if (data.pid1 == 0)
		first_child(data);
	data.pid2 = fork();
	if (data.pid2 == 0)
		second_child(data);
	error(data);
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	waitpid(data.pid1, &status, 0);
	waitpid(data.pid2, &status, 0);
	free_parent(&data);
	return (WEXITSTATUS(status));
}


void	first_child(t_data data)
{
	dup2(data.pipe_fd[1], OUT);
	close(data.pipe_fd[0]);
	dup2(data.fd_in, IN);
	data.cmd_args = ft_split(data.argv[2], ' ');
	execute(data);
}


}

/*

//FROM pipex.c

static int	file_open(char *file, int mode, t_data data)
{
	int	i;

	i = 0;
	if (mode == IN)
		i = (open(file, O_RDONLY));
	else
		i = (open(file, O_TRUNC | O_CREAT | O_RDWR, 0644));
	if (i < 0)
		error(data);
	return (i);
}



//FROM execute_cmd.c

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	write(STDERR_FILENO, INV_CMD, ft_strlen(INV_CMD));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

static void	execute(t_data data)
{
	data.cmd = get_cmd(data.cmd_path, data.cmd_args[0]);
	if (!data.cmd)
	{
		free_child(&data);
		free_parent(&data);
		exit(EXIT_INVCMD);
	}
	execve(data.cmd, data.cmd_args, data.envp);
}

void	first_child(t_data data)
{
	dup2(data.pipe_fd[1], OUT);
	close(data.pipe_fd[0]);
	dup2(data.fd_in, IN);
	data.cmd_args = ft_split(data.argv[2], ' ');
	execute(data);
}

void	second_child(t_data data)
{
	dup2(data.pipe_fd[0], IN);
	close(data.pipe_fd[1]);
	dup2(data.fd_out, OUT);
	data.cmd_args = ft_split(data.argv[3], ' ');
	execute(data);
}



//FROM errors.c


void	error(t_data data)
{
	if (data.pid1 == -1 || data.pid2 == -1)
	{
		perror(FORK);
		exit(1);
	}
	if (data.pipe_status == -1)
	{
		free_parent(&data);
		perror(PIPE);
		exit(1);
	}
}

void	error_file(t_data data)
{
	if (data.fd_in == -1)
	{
		free_parent(&data);
		write(STDERR_FILENO, ACCESS_DEN, ft_strlen(ACCESS_DEN));
		write(STDERR_FILENO, data.argv[1], ft_strlen(data.argv[1]));
		exit(0);
		if (access(data.argv[1], F_OK))
		{
			write(STDERR_FILENO, NO_FILE, ft_strlen(NO_FILE));
			write(STDERR_FILENO, data.argv[1], ft_strlen(data.argv[1]));
			exit(0);
		}
	}
	if (data.fd_out == -1)
	{
		free_parent(&data);
		write(STDERR_FILENO, ACCESS_DEN, ft_strlen(ACCESS_DEN));
		write(STDERR_FILENO, data.argv[4], ft_strlen(data.argv[4]));
		exit(127);
	}
}

void	error_args(t_data data)
{
	free_parent(&data);
	ft_putstr_fd(ARGS_MSG, STDERR_FILENO);
	exit(1);
}

void	free_parent(t_data *data)
{
	int	i;

	i = 0;
	close(data->fd_in);
	close(data->fd_out);
	while (data->cmd_path[i])
	{
		free(data->cmd_path[i]);
		i++;
	}
	free(data->cmd_path);
}

void	free_child(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
}

*/