/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:28:58 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 19:34:45 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	int		maxlen;
	char	*buff;

	i = 0;
	j = 0;
	len = ft_strlen((char *)s1);
	maxlen = len + ft_strlen((char *)s2);
	buff = malloc((maxlen + 1) * sizeof(char));
	if (!buff)
		return (0);
	while (i < len)
	{
		buff[i] = s1[i];
		i++;
	}
	while (i < maxlen)
		buff[i++] = s2[j++];
	buff[i] = '\0';
	return ((char *)buff);
}

/* #include<stdio.h>
int main()
{
	char str1[] = "From the Grandline";
	char str2[] = "To the Newworld";
	printf("%s\n", ft_strjoin(str1, str2));
} */