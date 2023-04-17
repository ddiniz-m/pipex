/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:31:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:30:54 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	path_init(t_pipex *pipex, char **env)
{
	char	*env_path;

	while (ft_strnstr(*++env, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*env, "PATH=");
	pipex->paths = ft_split2(env_path, ':');
	free(env_path);
}

char	*get_cmd(t_pipex *pipex, char *cmd)
{
	int	i;
	char *buf;

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
