/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:15 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/11 21:22:23 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	return (flag);
}

int		flag_mngr(va_list va, const char *format, int *i)
{
	++(*i);
	if (flag(&format[*i]) == 'd')
		ft_putnbr(va_arg(va, int));
	else if (flag(&format[*i]) == 's')
		ft_putstr(va_arg(va, char *));
	else if (flag(&format[*i]) == '%')
		ft_putchar('%');
	else if (flag(&format[*i]) == 'c')
		ft_putchar(va_arg(va, int));
	else if (flag(&format[*i]) == 'p')
		write(1, va_arg(va, void *), 1);
	++(*i);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	va_list va;

	i = 0;
	va_start(va, format);
	while (format[i])
	{
		if (format[i] == '%')
			flag_mngr(va, format, &i);
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
	ft_printf("integer : %i \nstring : %s\n%%\nchar : %c\npointer : %p\nend of printf", 120301, "sample string", 67, *s);
	return (0);
}