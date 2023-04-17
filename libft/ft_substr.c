/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:54:21 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:10:50 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/pipex.h"

char	*ft_substr(char *s, int start, size_t len)
{
	size_t	i;
	char	*buff;

	i = 0;
	if (start >= ft_strlen(s))
	{
		buff = malloc(sizeof(char));
		buff[0] = '\0';
		return (buff);
	}
	if (ft_strlen(s) - (unsigned int)start >= len)
		buff = malloc((len + 1) * sizeof(char));
	else
		buff = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (!buff)
		return (0);
	while (s[start] && i < len && start < ft_strlen(s))
	{
		buff[i] = s[start];
		start++;
		i++;
	}
	buff[i] = '\0';
	return (buff);
	free(buff);
}

/* #include<stdio.h>
int	main()
{
	char str[] = "hola";
	printf ("%s\n", ft_substr(str, 0, 5));
	return(0);
} */