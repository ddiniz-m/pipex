/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:41:40 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/03/23 13:54:34 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_putnbr(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		if (nb == -2147483648)
			return (write(1, "-2147483648", 11));
		i += ft_putchar('-');
		i += ft_putnbr(-nb);
	}
	else
	{
		if (nb > 9)
			i += ft_putnbr(nb / 10);
		i += ft_putchar((nb % 10) + 48);
	}
	return (i);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (*str != '\0')
		i += write(1, str++, 1);
	return (i);
}
