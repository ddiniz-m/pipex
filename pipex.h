/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:53:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 19:55:36 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

#include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

//----------------------------------PIPEX--------------------------------------
typedef struct	s_pipex
{
	int pipefd[2];
	char	**cmd1;
	char	**cmd2;
	char	**paths;
}				t_pipex;

//----------------------------------LIBFT--------------------------------------
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strnstr(const char *str, const char *to_find, size_t n);
unsigned int	ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
//----------------------------------PRINTF-------------------------------------
int					ft_printf(const char *str, ...);
int					ft_puthexa(unsigned long long nbr,
						unsigned long long base, int i);
int					ft_check(char str, va_list args);
int					ft_putstr(char *str);
int					ft_putchar(char c);
int					ft_putnbr(int nb);
int					ft_putptr(unsigned long nbr);

#endif