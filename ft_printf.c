/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:15 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 22:09:30 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

t_flags	parce(const char *format, int i)
{
	t_flags	print;

	print = init_print();
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
	if (format[i - 1] == 'l' && format[i - 2] == 'l')
		print.flag = 'L';
	if (format[i - 1] == 'l' && format[i - 2] != 'l')
		print.flag = 'l';
	if (format[i - 1] == 'h' && format[i - 2] == 'h')
		print.flag = 'H';
	if (format[i - 1] == 'h' && format[i - 2] != 'h')
		print.flag = 'h';
	print.type = format[i];
	print.index = i;
	while (format[i] != '%' ? format[i] != '%' : 0)
		i--;
	++i;
	while (format[i] && !(format[i] > '0' && format[i] <= '9') && format[i] != '.' &&
	(format[i] != 'i' && format[i] != 'd' && format[i]
	!= 's' && format[i] != '%' && format[i] != 'c' && format[i] != 'p' &&
	format[i] != 'o' && format[i] != 'u' && format[i] != 'u' && format[i]
	!= 'x' && format[i] != 'X' && format[i] != 'f'))
	{
		if (format[i] == '-')
			print.minus = 'A';
		if (format[i] == '+')
			print.plus = 'A';
		if (format[i] == '0')
			print.zero = 'A';
		if (format[i] == '#')
			print.hash = 'A';
		if (format[i] == ' ')
			print.space = 'A';
		i++;
	}
	print.width = (format[i] >= '0' && format[i] <= '9' ? ft_atoi(&format[i]) : 0);
	if (print.precision == 1)
	{
		while (format[i] != '.')
			i++;
		print.precision = ft_atoi(&format[i + 1]);
	}
	return (print);
}

int		flag_mngr(va_list va, t_flags print)
{
	if (print.type == 'd' || print.type == 'i')
	{
		if (print.flag == 'l')
			put_int(ft_itoa((long)va_arg(va, int)), print);
		else if (print.flag == 'L')
			put_int(ft_itoa((long long)va_arg(va, int)), print);
		else if (print.flag == 'h')
			put_int(ft_itoa((unsigned char)va_arg(va, int)), print);
		else if (print.flag == 'H')
			put_int(ft_itoa((char)va_arg(va, int)), print);
		else
			put_int(ft_itoa(va_arg(va, int)), print);
	}
	else if (print.type == 'u')
		put_int_unsigned(ft_itoa_unsigned((unsigned int)va_arg(va, unsigned int)), print);
	else if (print.type == 's')
		putst(va_arg(va, char *), print);
	else if (print.type == '%')
	{
		g_count++;
		ft_putchar('%');
	}
	else if (print.type == 'c')
		ft_putchar(va_arg(va, int));
	else if (print.type == 'p')
		ft_putaddr((int)va_arg(va, void *), 0, print);
	else if (print.type == 'o')
		put_int_unsigned(base_10_trans(va_arg(va, unsigned int), 8), print);
	else if (print.type == 'x')
		base_16_trans(va_arg(va, unsigned int), 0, print);
	else if (print.type == 'X')
		base_16_trans(va_arg(va, unsigned int), 1, print);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	va_list va;
	t_flags print;
	int		len;

	len = ft_strlen(format);
	i = 0;
	va_start(va, format);
	while (i < len)
	{
		if (format[i] == '%')
		{
			i++;
			print = parce(format, i);
			flag_mngr(va, print);
			i = print.index + 1;
		}
		if (i < len && format[i] != '%')
		{
			write(1, &format[i], 1);
			i++;
			g_count++;
		}
	}
	va_end(va);
	return (g_count);
}

int		main(void)
{
	char *s;

	s = "sda";
	ft_printf("[%+10.5d]", 4242);
	printf("[%+10.5d]", 4242);
	return (0);
}