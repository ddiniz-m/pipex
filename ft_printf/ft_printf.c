/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:47:19 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:11:27 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/pipex.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	va_start(args, str);
	count = 0;
	while (str && *str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '%')
				count += ft_putchar('%');
			else
				count += ft_check(*str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	int i;
	int j;

	i = ft_printf("Mine:(%s %i %x %X %p %c)\n", "Hello", 42, 42, 42, NULL, 'z');
	j = printf("Orig:(%s %i %x %X %p %c)\n", "Hello", 42, 42, 42, NULL, 'z');
	printf("\nMine: %i\n", i);
	printf("Orig: %i\n", j);
} */