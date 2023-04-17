/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:58:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:10:37 by ddiniz-m         ###   ########.fr       */
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

/* #include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		i;
	char	*str;
	char	c;
	int		j;
	char	**buff;

	i = 0;
	str = " Tripou   ille ";
	c = ' ';
	j = word_counter(str, c);
	buff = ft_split(str, c);
	while (i <= j)
	{
		printf("s: %s\n", buff[i]);
		i++;
	}
} */
/*
15: When it enword_counters "c" checks if the next character 
is not "c" and adds 1 to "words".If this condition is 
not true, it just keeps checking every character until
it finds another "c" that hasn't "c" as the next character

58: Create **buffer with enough memory for total number of
	words + \0;
63: Skips any instance of c in the beginning of the string
65: When it reaches a "word" counts how many characters it
	has --> i;
66: Condition in case there are no characters that are not
	"c";
68: Allocates the size of the first word (i) + 1 for \0;
69-63: Resets i so it can copy the word into temp and add /0
	at the end of the string;
74: Copies temp into the respective buff pointer;
*/