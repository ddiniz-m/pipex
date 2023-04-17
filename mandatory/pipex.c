/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 17:53:42 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_pipex *pipex, char **env)
{
	int		i;
	char	*str;

	i = 0;
	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close_all(pipex);
	close(0);
	str = get_cmd(pipex, pipex->cmd1[0]);
	if (execve(str, pipex->cmd1, env) == -1)
		perror("cmd1");
	close_all(pipex);
}

void	parent(t_pipex *pipex, char **env)
{
	int		i;
	int		status;
	char	*str;

	i = 0;
	waitpid(-1, &status, 0);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close_all(pipex);
	str = get_cmd(pipex, pipex->cmd2[0]);
	if (execve(str, pipex->cmd2, env) == -1)
		perror("cmd2");
	close_all(pipex);
}

void	pipe_x(t_pipex *pipex, char **env)
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
		child(pipex, env);
	else
		parent(pipex, env);
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_printf("Incorret amount of arguments\n");
		return (0);
	}
	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
		return (0);
	pipex.fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.fd_outfile < 0)
	{
		close(pipex.fd_infile);
		return (0);
	}
	var_init(&pipex, av, env);
	pipe_x(&pipex, env);
	free_all(&pipex);
	return (0);
}
