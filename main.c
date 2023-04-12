/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/12 17:53:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	var_init(t_pipex *pipex, char **av, char **env)
{
	char	*buff;
	char	*env_path;

	while (ft_strnstr(*++env, "PATH=", 5) == NULL);
	env_path = *env;
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->paths = ft_split2(env_path, ':');
	buff = pipex->paths[0];
	pipex->paths[0] = ft_strtrim(buff, "PATH=");
	free(buff);
}

void	child(t_pipex *pipex, int fd_infile, char **env)
{
	int		i;
	char	*str;

	i = 0;
	close(pipex->pipefd[0]);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	dup2(fd_infile, STDIN_FILENO);
	while ((pipex->paths)[++i])
	{
		str = ft_strjoin(pipex->paths[i], pipex->cmd1[0]);
		if (!access(str, F_OK))
			break ;
		free(str);
	}
	close(pipex->pipefd[1]);
	close(fd_infile);
	if (execve(str, pipex->cmd1, env) == -1)
		perror("cmd1");
}

void	parent(t_pipex *pipex, int fd_outfile, char **env)
{
	int		i;
	char	*str;

	i = 0;
	wait(NULL);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(pipex->pipefd[1]);
	
	while ((pipex->paths)[++i])
	{
		str = ft_strjoin((pipex->paths)[i], pipex->cmd2[0]);
		if (!access(str, F_OK))
			break ;
		free(str);
	}
	close(pipex->pipefd[0]);
	close(fd_outfile);
	if (execve(str, pipex->cmd2, env))
		perror("cmd2");
	return ;
}

void	pipe_x(t_pipex *pipex, int fd_infile, int fd_outfile, char **env)
{
	pid_t	pid;

	if (pipe(pipex->pipefd) < 0)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		return ;
	}
	if (pid == 0)
		child(pipex, fd_infile, env);
	else
		parent(pipex, fd_outfile, env);
	return ;
}

int	main(int ac, char **av, char **env)
{
	int	fd_infile;
	int	fd_outfile;
	t_pipex	pipex;
	
	if (ac != 5)
	{
		ft_printf("Incorret amount of arguments\n");
		return (0);
	}
	if (put_error(av) != 0)
		return (0);
	fd_infile = open(av[1], O_RDONLY);
	fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_infile < 0 || fd_outfile < 0)
		return (0);
	var_init(&pipex, av, env);
	pipe_x(&pipex, fd_infile, fd_outfile, env);
	free_arr(pipex.paths);
	free_arr(pipex.cmd1);
	free_arr(pipex.cmd2);
	return (0);
}