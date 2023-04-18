/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:58:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/18 15:52:18 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/pipex.h"

int	word_counter2(char const *s, int c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

int	word_size2(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

char	*make_temp2(int i, char const *s, char c)
{
	char	*temp;

	temp = NULL;
	temp = (char *)malloc((i + 2) * sizeof(char));
	i = 0;
	while (*s && *s != c)
		temp[i++] = *s++;
	temp[i++] = 47;
	temp[i] = '\0';
	return (temp);
}

char	**ft_split2(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**buff;

	j = 0;
	count = word_counter2(s, c);
	buff = (char **)malloc((count + 1) * sizeof(char *));
	if (!buff)
		return (0);
	while (j < count)
	{
		while (*s && *s == c && j != count)
			s++;
		i = word_size2(s, c);
		buff[j++] = make_temp2(i, s, c);
		s = s + i + 1;
	}
	buff[j] = 0;
	return (buff);
}
