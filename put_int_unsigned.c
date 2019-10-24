/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:25:29 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/24 14:20:50 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itoa_uns(char *str, uintmax_t nb, uintmax_t i)
{
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		i--;
		nb /= 10;
	}
}

char		*ft_itoa_unsigned(uintmax_t n, t_flags print)
{
	uintmax_t				i;
	uintmax_t	buf;
	char				*str;
	uintmax_t	nb;

	if (!n)
		return (print.dot && !print.precision ? "" : "0");
	nb = (uintmax_t)n;
	i = 0;
	buf = nb;
	while (buf > 0)
	{
		buf = buf / 10;
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	itoa_uns(str, nb, i);
	return (str);
}

void	put_int_unsigned(char *str, t_flags print)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(str);
	if (print.precision || print.dot || print.minus)
		print.zero = '\0';
	print.width -= (print.precision > len ? print.precision : len);
	print.precision -= len - (str[i] == '-' ? 1 : 0);
	if (print.minus)
	{
		while (print.precision > 0)
		{
			write(1, "0", 1);
			print.precision--;
			g_count++;
		}
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
			g_count++;
		}
		while (print.width > 0)
		{
			write(1, " ", 1);
			print.width--;
			g_count++;
		}
	}
	else
	{
		while ((print.width > 0 || print.precision > 0) && print.zero)
		{
			write(1, "0", 1);
			print.width--;
			g_count++;
			print.precision--;
		}
		while (print.width > 0 && !print.zero)
		{
			write(1, " ", 1);
			print.width--;
			g_count++;
		}
		while (print.precision > 0)
		{
			write(1, "0", 1);
			print.precision--;
			g_count++;
		}
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
			g_count++;
		}
	}
	if (!(*str == '0' && !str[1]) && *str)
		free(str);
}
