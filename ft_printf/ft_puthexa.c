/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:39:47 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 13:54:29 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	conv(unsigned long long nbr, unsigned long long base, char *base_str)
{
	int	count;

	count = 0;
	if (nbr >= base)
		count += conv(nbr / base, base, base_str);
	return (ft_putchar(base_str[nbr % base]) + count);
}

int	ft_putptr(unsigned long nbr)
{
	if (nbr == 0)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_puthexa(nbr, 16, 1));
}

int	ft_puthexa(unsigned long long nbr, unsigned long long base, int i)
{
	int	count;

	count = 0;
	if (i == 0)
		count += conv(nbr, base, "0123456789ABCDEF");
	if (i == 1)
		count += conv(nbr, base, "0123456789abcdef");
	return (count);
}
