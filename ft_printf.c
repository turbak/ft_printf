/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:15 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/16 20:32:16 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		charcheck(char c)
{
	return (c != 'i' && c != 'd' && c != 's' && c != 'S'
	&& c != '%' && c != 'c' && c != 'p' && c != 'U' &&
	c != 'o' && c != 'u' && c != 'u' && c != 'x' && c != 'C'
	&& c != 'X' && c != 'f' && c != 'D' && c != 'O');
}

t_flags	parce(const char *format, int i)
{
	t_flags	print;

	print = init_print();
	print.precision = 0;
	while (format[i] && charcheck(format[i]))
	{
		if (format[i] == '.')
			print.dot = 'A';
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
	i -= (print.type == '%' ? 1 : 0);
	while (format[i] != '%' ? format[i] != '%' : 0)
		i--;
	++i;
	while (format[i] && !(format[i] > '0' && format[i] <= '9') &&
	format[i] != '.' && charcheck(format[i]))
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
	if (print.dot)
	{
		while (format[i] != '.')
			i++;
		print.precision = ft_atoi(&format[i + 1]);
	}
	return (print);
}

int		flag_mngr(va_list va, t_flags print)
{
	if (print.type == 'd' || print.type == 'i' || print.type == 'D')
	{
		if (print.flag == 'l' || print.type == 'D')
			put_int(ft_itoa((intmax_t)va_arg(va, long)), print);
		else if (print.flag == 'L')
			put_int(ft_itoa((intmax_t)va_arg(va, long long)), print);
		else if (print.flag == 'h')
			put_int(ft_itoa((intmax_t)((short)va_arg(va, int))), print);
		else if (print.flag == 'H')
			put_int(ft_itoa((intmax_t)((char)va_arg(va, int))), print);
		else
			put_int(ft_itoa((intmax_t)va_arg(va, int)), print);
	}
	else if (print.type == 'u' || print.type == 'U')
	{
		if (print.flag == 'l')
			put_int_unsigned(ft_itoa_unsigned((uintmax_t)((size_t)va_arg(va, long)), print), print, '0');
		else if (print.flag == 'L')
			put_int_unsigned(ft_itoa_unsigned((uintmax_t)((size_t)va_arg(va, long long)), print), print, '0');
		else if (print.flag == 'h')
			put_int_unsigned(ft_itoa_unsigned(((unsigned short)va_arg(va, int)), print), print, '0');
		else if (print.flag == 'H')
			put_int_unsigned(ft_itoa_unsigned((uintmax_t)((char)va_arg(va, int)), print), print, '0');
		else
			put_int_unsigned(ft_itoa_unsigned((uintmax_t)((size_t)va_arg(va, size_t)), print), print, '0');
	}
	else if (print.type == 'S' || (print.type == 's' && print.flag == 'l'))
		putstl(va_arg(va, wchar_t *), print);
	else if (print.type == 's')
		putst((va_arg(va, char *)), print);
	else if (print.type == '%')
	{
		put_char('%', print);
	}
	else if (print.type == 'c')
		put_char((unsigned char)va_arg(va, int), print);
	else if (print.type == 'C')
		put_char(va_arg(va, wchar_t), print);
	else if (print.type == 'p')
	{
		print.hash = 'A';
		put_int_unsigned(base_16_trans((uintmax_t)va_arg(va, void *), 0, print), print, '2');
	}
	else if (print.type == 'o' || print.type == 'O')
	{
		if (print.flag == 'l')
			put_int_unsigned(base_10_trans(((uintmax_t)(size_t)va_arg(va, unsigned long)), 8, print), print, '1');
		else if (print.flag == 'L')
			put_int_unsigned(base_10_trans((uintmax_t)((size_t)va_arg(va, long long)), 8, print), print, '1');
		else if (print.flag == 'h')
			put_int_unsigned(base_10_trans((unsigned short)va_arg(va, int), 8, print), print, '1');
		else if (print.flag == 'H')
			put_int_unsigned(base_10_trans((unsigned char)va_arg(va, int), 8, print), print, '1');
		else
			put_int_unsigned(base_10_trans((uintmax_t)(va_arg(va, size_t)), 8, print), print, '1');
	}
	else if (print.type == 'x' || print.type == 'X')
	{
		if (print.flag == 'l')
			put_int_unsigned(base_16_trans((uintmax_t)((size_t)va_arg(va, long)), (print.type == 'x' ? 0 : 1), print), print, '2');
		else if (print.flag == 'L')
			put_int_unsigned(base_16_trans((uintmax_t)((size_t)va_arg(va, long long)), (print.type == 'x' ? 0 : 1), print), print, '2');
		else if (print.flag == 'h')
			put_int_unsigned(base_16_trans((unsigned short)va_arg(va, int), (print.type == 'x' ? 0 : 1), print), print, '2');
		else if (print.flag == 'H')
			put_int_unsigned(base_16_trans((unsigned char)va_arg(va, int), (print.type == 'x' ? 0 : 1), print), print, '2');
		else
			put_int_unsigned(base_16_trans((va_arg(va, size_t)), (print.type == 'x' ? 0 : 1), print), print, '2');
	}
	else if (print.type == 'f')
		put_int(ft_dtoa(va_arg(va, double), &print), print);
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

/*int		main(void)
{
	printf("test%---10.6x et %01hhX !!\n", 0xaabb, (unsigned char)0);
	ft_printf("test%---10.6x et %01hhX !!\n", 0xaabb, (unsigned char)0);
	return (0);
}*/