/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:49:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 17:53:45 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*buf;

	i = 0;
	while ((pipex->paths)[i])
	{
		buf = ft_strjoin(pipex->paths[i], cmd);
		if (!access(buf, F_OK))
			return (buf);
		free(buf);
		i++;
	}
	return (NULL);
}

void	var_init(t_pipex *pipex, char **av, char **env)
{
	char	*env_path;

	while (ft_strnstr(*++env, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*env, "PATH=");
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->paths = ft_split2(env_path, ':');
	free(env_path);
}
