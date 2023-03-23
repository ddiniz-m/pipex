/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:10:28 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 18:12:59 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((int)n < 0)
		n = ft_strlen(str) - 1;
	if (*to_find == '\0')
		return ((char *)str + i);
	while (str[i] && i < n)
	{
		while (str[i] != to_find[j])
			i++;
		while (to_find[j] && str[i] == to_find[j] && i < n)
		{
			i++;
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)str + (i - j));
		i = i - (j - 1);
		j = 0;
	}
	return (0);
}

/* #include <stdio.h>

int main()
{
	const char *s1;
	const char *s2;
	
	s1 = "ccaaabcasdar";
	s2 = "aab";
	printf("Result: %s\n", ft_strnstr(s1, s2, 30));
}
 */