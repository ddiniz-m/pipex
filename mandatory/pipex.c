/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/19 17:40:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_pipex *pipex, char **envp, char **av)
{
	char	*str;
	char	**cmd;
	char	**paths;

	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close_all(pipex);
	paths = path_init(envp);
	cmd = ft_split(av[2], ' ');
	str = get_cmd(cmd[0], paths);
	free_arr(paths);
	if (!str || execve(str, cmd, envp) == -1)
		perror("cmd1");
	free(str);
	free_arr(cmd);
	close_all(pipex);
	exit(1);
}

void	parent(t_pipex *pipex, char **envp, char **av)
{
	char	*str;
	char	**cmd;
	char	**paths;

	wait(NULL);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close_all(pipex);
	paths = path_init(envp);
	cmd = ft_split(av[3], ' ');
	str = get_cmd(cmd[0], paths);
	free_arr(paths);
	if (!str || execve(str, cmd, envp) == -1)
		perror("cmd2");
	free(str);
	free_arr(cmd);
	close_all(pipex);
	exit (1);
}

void	pipe_x(t_pipex *pipex, char **envp, char **av)
{
	pid_t	pid;

	if (pipe(pipex->pipefd) == -1)
	{
		perror("Pipe");
		exit (1) ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		exit(1);
	}
	if (pid == 0)
		child(pipex, envp, av);
	else
		parent(pipex, envp, av);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_printf("Incorret amount of arguments\n");
		return (0);
	}
	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
	{
		perror("Infile");
		return(1);
	}
	pipex.fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.fd_outfile < 0)
		return (1);
	pipe_x(&pipex, envp, av);
	return (0);
}
