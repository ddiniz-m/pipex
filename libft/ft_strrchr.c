/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:22:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:10:47 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/pipex.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen((char *)s) - 1;
	if ((char) c == '\0')
		return ((char *)s + len + 1);
	while (s[len] != s[-1])
	{
		if (s[len] == (char) c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}

/* 
20-21: If c is NULL, because we are dealing with string REVERSE character
	the firts character the functions searches will be the \0 at the
	end of the string. So, it just returns NULL;
22: If not for the -1, it would skip s[0] which is our 1st character;
 */

/* #include<stdio.h>

int main()
{
	char str[] = "hello.tcom.pt";
	int c = 't' + 256;
	printf("%s\n", ft_strrchr(str, c));
} */