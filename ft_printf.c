/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:15 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/25 20:52:17 by cauranus         ###   ########.fr       */
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
	if ((format[i - 1] == 'l' && format[i - 2] == 'l') || format[i - 1] == 'L')
		print.flag = 'L';
	else if (format[i - 1] == 'l' && format[i - 2] != 'l')
		print.flag = 'l';
	else if (format[i - 1] == 'h' && format[i - 2] == 'h')
		print.flag = 'H';
	else if (format[i - 1] == 'h' && format[i - 2] != 'h')
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
	if (get_flags(va, print))
		return (0);
	else if (print.type == 'p')
	{
		print.hash = 'A';
		put_16x(put_addr((uintmax_t)va_arg(va, void *), print), print);
	}
	else if (print.type == 'o' || print.type == 'O')
		get_o(va, print);
	else if (print.type == 'x' || print.type == 'X')
	{
		print.hash = (print.type == 'X' && print.hash ? 'B' : print.hash);
		get_x(va, print);
	}
	else if (print.type == 'f')
	{
		print.precision = (!print.precision ? 6 : print.precision);
		if (print.flag == 'L')
			put_int(ft_dtoa(va_arg(va, long double), &print), print);
		else
			put_int(ft_dtoa(va_arg(va, double), &print), print);
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	va_list va;
	t_flags print;

	i = 0;
	va_start(va, format);
	g_count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			print = parce(format, i);
			flag_mngr(va, print);
			i = print.index + (format[i] ? 1 : 0);
		}
		if (format[i] && format[i] != '%')
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
	int i;
	char *s;

	s = "123";
	ft_printf("%");
	//printf("[%d]\n", ft_printf("[%ls]", L"sd"));
	//printf("{%d}", printf("{%ls}", L"sd"));
	return (0);
}
*/