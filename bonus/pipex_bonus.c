/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:03:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:39:43 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	child_process(t_pipex *pipex, char **av, int *fd, int arg, char **env)
{
	char **buff;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	/* close_all(pipex, fd); */
	buff = ft_split(av[arg], ' ');
	if (execve(get_cmd(pipex, buff[0]), buff, env) == -1)
		perror("Command not found");
	close_all(pipex, fd);
	exit (0);
}

void	pipe_fork(t_pipex *pipex, int *fd, char **av, int arg, char **env)
{
	pid_t child;

	if(pipe(fd) == -1)
	{
		perror("Pipe");
		exit (1);
	}
	child = fork();
	if (child == -1)
	{
		perror("Fork");
		exit (1);
	}
	if (child == 0)
		child_process(pipex, av, fd, arg, env);
	else
	{
		close(fd[1]);
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		/* close_all(pipex, fd); */
	}
}

int	infile(t_pipex *pipex, char **av)
{
	pipex->fd_infile = open(av[1], O_RDONLY);
	if (pipex->fd_infile < 0)
	{
		perror("Infile");
		return (1);
	}
	dup2(pipex->fd_infile, STDIN_FILENO);
	close(pipex->fd_infile);
	return (0);
}

int	outfile(t_pipex *pipex, char **av, int ac, char **env)
{
	char **buff;
	
	pipex->fd_outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
	{
		perror("Outfile");
		close(pipex->fd_infile);
		return (1);
	}
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	buff = ft_split(av[ac - 2], ' ');
	if (execve(get_cmd(pipex, buff[0]), buff, env) == -1)
		perror(buff[0]);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	arg;
	int fd[2];
	t_pipex	pipex;

	if (ac < 5)
		return (printf("Not enough arguments"));
	path_init(&pipex, env);
	if(infile(&pipex, av) != 0)
		return (1);
	arg = 2;
	while(arg != ac - 1)
		pipe_fork(&pipex, fd, av, arg++, env);
	if(outfile(&pipex, av, ac, env) != 0)
		return (1);
	close_all(&pipex, fd);
	return (0);
}