/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/30 20:53:38 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	var_init(t_pipex *pipex, char **av, char **env)
{
	char *buff;
	char	*env_path;
	
	while(ft_strnstr(*++env, "PATH=", 5) == NULL);
	env_path = *env;
	pipex->env = env;
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->paths = ft_split2(env_path, ':');
	buff = pipex->paths[0];
	pipex->paths[0] = ft_strtrim(buff, "PATH=");
	free(buff);
}

int	child(t_pipex *pipex, int fd_infile)
{
	int		i;
	int		exec;
	char	*str;

	i = 0;
	dup2(fd_infile, 0);
	dup2(pipex->pipefd[1], 1);

	close(fd_infile);
	close(pipex->pipefd[0]);

	while((pipex->paths)[++i])
	{
		str = ft_strjoin(pipex->paths[i], pipex->cmd1[0]);
		if(!access(str, F_OK))
			break ;
		free(str);
	}
	if(access(str, F_OK))
			perror(*pipex->cmd1);
	exec = execve(str, pipex->cmd1, pipex->env);
	if (exec == -1)
		perror("cmd1");
	return (1);
}

int	parent(t_pipex *pipex, int fd_outfile)
{
	int		i;
	char	*str;
	int		exec;
	int		status;

	i = 0;
	waitpid(-1, &status, 0);
	dup2(fd_outfile, 1);
	dup2(pipex->pipefd[0], 0);

	close(fd_outfile);
	close(pipex->pipefd[1]);

	while((pipex->paths)[++i])
	{
		str = ft_strjoin((pipex->paths)[i], pipex->cmd2[0]);
		if(!access(str, F_OK))
			break ;
		free(str);
	}
	exec = execve(str, pipex->cmd2, pipex->env);
	if (exec == -1)
		perror("cmd2");
	return (1);
}

int	pipe_x(t_pipex *pipex, int fd_infile, int fd_outfile)
{
	pid_t	pid;
	if(pipe(pipex->pipefd) < 0)
		return (-1);

	pid = fork();
	if(pid < 0)
	{
		perror("Fork");
		return (1);
	}
	if(!pid)
		child(pipex, fd_infile);
	else
		parent(pipex, fd_outfile);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	fd_infile;
	int	fd_outfile;
	t_pipex	pipex;

	if(ac != 5)
	{
		ft_printf("Incorret amount of arguments\n");
		return (0);
	}
	if(put_error(av) != 0)
		return (1);
	fd_infile = open(av[1], O_RDONLY);
	fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_infile < 0 || fd_outfile < 0)
		return (1);
	var_init(&pipex, av, env);
	pipe_x(&pipex, fd_infile, fd_outfile);
	free_arr(pipex.cmd1);
	free_arr(pipex.cmd2);
	free_arr(pipex.paths);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	close(fd_infile);
	close(fd_infile);
	return (0);
}