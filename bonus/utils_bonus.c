/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:31:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/18 17:58:39 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**path_init(char **env)
{
	char **paths;
	char	*env_path;

	while (ft_strnstr(*++env, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*env, "PATH=");
	paths = ft_split2(env_path, ':');
	free(env_path);
	return (paths);
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
