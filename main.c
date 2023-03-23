/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 20:21:55 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ./pipex cmd1 file1 file2 cmd2
// ./pipex ls xinfile.txt xoutfile.txt wc -l

void	var_init(char **av, char **env)
{
	t_pipex	pipex;
	char	*env_path;
	
	while(ft_strnstr(*++env, "PATH=", 5) == NULL);
	env_path = *env;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.paths = ft_split(env_path, ':');
	while(*(pipex.cmd1++))
		printf("cmd1 = %s\n", *(pipex.cmd1));
	while(*(pipex.cmd2++))
		printf("cmd2 = %s\n", *(pipex.cmd2));
	while(*(pipex.paths++))
		printf("paths = %s\n", *(pipex.paths));
}

int	child(t_pipex *pipex, int fd_infile, char *cmd)
{
	int		i;

	i = 0;
	dup2(fd_infile, 0);
	dup2(pipex->pipefd[1], 1);

	close(fd_infile);
	close(pipex->pipefd[1]);
	
	while((pipex->paths)[++i])
	{
		cmd = ft_strjoin(ft_strjoin((pipex->paths)[i], "\\"), cmd);
		execve(cmd, pipex->cmd1, NULL);
		perror("cmd: doesn't exist");
		free(cmd);
	}
	return (-1);
}

int	parent(t_pipex *pipex, int fd_outfile, char *cmd)
{
	int		i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	dup2(fd_outfile, 1);
	dup2(pipex->pipefd[0], 0);

	close(fd_outfile);
	close(pipex->pipefd[0]);

	while((pipex->paths)[++i])
	{
		cmd = ft_strjoin(ft_strjoin((pipex->paths)[i], "\\"), cmd);
		execve(cmd, pipex->cmd2, NULL);
		perror("cmd: doesn't exist");
		free(cmd);
	}
	return (-1);
}

int	pipex(int fd_infile, int fd_outfile, char **av)
{
	t_pipex pipex;
	pid_t	pid;

	if(pipe(pipex.pipefd) < 0)
		return (0);

	pid = fork();
	if(pid < 0)
	{
		perror("Fork: ");
		return (0);
	}
	if(!pid)
		child(&pipex, fd_infile, av[2]);
	else
		parent(&pipex, fd_outfile, av[3]);
	return(0);
}

int	main(int ac, char **av, char **env)
{
	/* (void)ac; */
	int	fd_infile;
	int	fd_outfile;
	
	if(ac != 5)
		return (0);
	fd_infile = open(av[1], O_RDONLY);
	fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (fd_infile < 0 || fd_outfile < 0)
		return (0);
	var_init(av, env);
	pipex(fd_infile, fd_outfile, av);
	/* if (access(av[1], F_OK) < 0)
		return (0); */
	return (0);
}