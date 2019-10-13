/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:15 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 16:12:29 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

t_flags	parce(const char *format, int i)
{
	t_flags	print;

	print.precision = 0;
	while (format[i] && format[i] != 'i' && format[i] != 'd' && format[i]
	!= 's' && format[i] != '%' && format[i] != 'c' && format[i] != 'p' &&
	format[i] != 'o' && format[i] != 'u' && format[i] != 'u' && format[i]
	!= 'x' && format[i] != 'X' && format[i] != 'f')
	{
		if (format[i] == '.')
			print.precision = 1;
		i++;
	}
	print.type = format[i];
	print.index = i;
	while (format[i] != '%' ? format[i] != '%' : 0)
		i--;
	++i;
	if (!(format[i] > '0' && format[i] <= '9'))
	{
		print.flag = format[i];
		i++;
	}
	else
		print.flag = '\0';
	print.width = (format[i] >= '0' && format[i] <= '9' ? ft_atoi(&format[i]) : 0);
	if (print.precision == 1)
	{
		while (format[i] != '.')
			i++;
		print.precision = ft_atoi(&format[i + 1]);
	}
	return (print);
}

char	flag(const char *str)
{
	char flag;

	if (*str == 'i' || *str == 'd')
		flag = 'd';
	if (*str == 's')
		flag = 's';
	if (*str == '%')
		flag = '%';
	if (*str == 'c')
		flag = 'c';
	if (*str == 'p')
		flag = 'p';
	if (*str == 'o')
		flag = 'o';
	if (*str == 'u')
		flag = 'u';
	if (*str == 'x')
		flag = 'x';
	if (*str == 'X')
		flag = 'X';
	return (flag);
}

int		flag_mngr(va_list va, t_flags print)
{
	if (print.type == 'd' || print.type == 'i')
		put_int(ft_itoa(va_arg(va, int)), print);
	else if (print.type == 'u')
		ft_putnbr_unsigned((unsigned int)va_arg(va, unsigned int));
	else if (print.type == 's')
		ft_putstr(va_arg(va, char *));
	else if (print.type == '%')
		ft_putchar('%');
	else if (print.type == 'c')
		ft_putchar(va_arg(va, int));
	else if (print.type == 'p')
		ft_putaddr((int)va_arg(va, void *), 0);
	else if (print.type == 'o')
		base_10_trans(va_arg(va, unsigned int), 8);
	else if (print.type == 'x')
		base_16_trans(va_arg(va, unsigned int), 0);
	else if (print.type == 'X')
		base_16_trans(va_arg(va, unsigned int), 1);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	va_list va;
	t_flags print;

	i = 0;
	va_start(va, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			print = parce(format, i);
			flag_mngr(va, print);
			i = print.index + 1;
		}
		write(1, &format[i], 1);
		i++;
	}
	va_end(va);
	return (0);
}

int		main(void)
{
	char *s;

	s = "sda";
	ft_printf("integer : [%+100i]\nstring : %s\n%%\nchar : %c\npointer : %p\nend of printf", 120301, "sample string", 67, *s);
	printf("%+100i", 1234);
	return (0);
}