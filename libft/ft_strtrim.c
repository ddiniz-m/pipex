/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:38:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:10:48 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/pipex.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	char		*buff;

	if (!s1)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i--;
	if (i < 0)
	{
		buff = (char *)malloc(sizeof(char));
		buff[0] = '\0';
		return (buff);
	}
	i++;
	buff = (char *)malloc((i + 1) * sizeof(char));
	if (!buff)
		return (0);
	ft_strlcpy(buff, s1, i + 1);
	return ((char *)buff);
}

/*
20: Eliminates all characters corresponding to "set" from beginning of
	the string by searching all *s characters that are equal to any *set
	character;
*/
/* #include<stdio.h>

int	main()
{
	char str[] = "aaaaaaa";
	char trim[] = "a";
	printf("Result = %s\n", ft_strtrim(str, trim));
} */