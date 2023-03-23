/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:30:08 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 13:54:21 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_check(char str, va_list args)
{
	if (str == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	if (str == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (str == 'p')
		return (ft_putptr(va_arg(args, unsigned long)));
	if (str == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (str == 'i')
		return (ft_putnbr(va_arg(args, unsigned int)));
	if (str == 'u')
		return (ft_puthexa(va_arg(args, unsigned int), 10, 1));
	if (str == 'x')
		return (ft_puthexa(va_arg(args, unsigned int), 16, 1));
	if (str == 'X')
		return (ft_puthexa(va_arg(args, unsigned int), 16, 0));
	return (0);
}
