/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:49:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/18 17:25:56 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **path_init(char **env)
{
	char	**paths;
	char	*env_path;

	while (ft_strnstr(*++env, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*env, "PATH=");
	paths = ft_split2(env_path, ':');
	free(env_path);
	return(paths);
}

char	*get_cmd(char *cmd, char **paths)
{
	int	i;
	char *buf;

	i = 0;
	while ((paths)[i])
	{
		buf = ft_strjoin(paths[i], cmd);
		if (!access(buf, F_OK))
			return (buf);
		free(buf);
		i++;
	}
	return (NULL);
}

