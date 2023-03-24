/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/24 19:01:13 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex cmd1 file1 file2 cmd2
// ./pipex ls xinfile.txt xoutfile.txt wc -l

void	var_init(t_pipex *pipex, char **av, char **env)
{
	char *buff;
	char	*env_path;
	
	while(ft_strnstr(*++env, "PATH=", 5) == NULL);
	env_path = *env;
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->paths = ft_split2(env_path, ':');
	buff = pipex->paths[0];
	pipex->paths[0] = ft_strtrim(buff, "PATH=");
	free(buff);
	/* int	i;
	i = 0;
	while(pipex->cmd1[i])
		printf("cmd1 = %s\n", (pipex->cmd1)[i++]);
	i = 0;
	while((pipex->cmd2)[i])
		printf("cmd2 = %s\n", (pipex->cmd2)[i++]);
	i = 0;
	while((pipex->paths)[i])
		printf("paths = %s\n", (pipex->paths)[i++]); */
}

int	child(t_pipex *pipex, int fd_infile, char *cmd)
{
	int		i;
	char	*buf;

	i = 1;
	dup2(fd_infile, 0);
	dup2(pipex->pipefd[1], 1);

	close(fd_infile);
	close(pipex->pipefd[0]);
	
	while((pipex->paths)[i++])
	{
		buf = ft_strjoin(pipex->paths[i], cmd);
		write(2, buf, strlen(buf));
		write(2, "\n", 1);
		execve(buf, &(*++pipex->cmd1), NULL);
		free(buf);
	}
	perror("cmd1");
	return (1);
}

int	parent(t_pipex *pipex, int fd_outfile, char *cmd)
{
	int		i;
	char	*buf;
	int		status;

	i = 0;
	waitpid(-1, &status, 0);
	dup2(fd_outfile, 1);
	dup2(pipex->pipefd[0], 0);

	close(fd_outfile);
	close(pipex->pipefd[1]);

	while((pipex->paths)[++i])
	{
		buf = ft_strjoin((pipex->paths)[i], cmd);
		execve(buf, pipex->cmd2, NULL);
		free(buf);
	}
	perror("cmd2");
	return (1);
}

int	pipe_x(t_pipex *pipex, int fd_infile, int fd_outfile, char **av)
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
		child(pipex, fd_infile, av[2]);
	else
		parent(pipex, fd_outfile, av[3]);
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
	pipe_x(&pipex, fd_infile, fd_outfile, av);
	free_arr(pipex.cmd1);
	free_arr(pipex.cmd2);
	free_arr(pipex.paths);
	return (0);
}