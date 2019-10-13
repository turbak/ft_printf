/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:25:29 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 20:30:43 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itoa_uns(char *str, long long nb, size_t i)
{
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		i--;
		nb /= 10;
	}
}

char		*ft_itoa_unsigned(unsigned int n)
{
	size_t				i;
	unsigned long long	buf;
	char				*str;
	unsigned long long	nb;

	nb = (unsigned long long)n;
	i = (nb > 0 ? 0 : 1);
	buf = (nb > 0 ? nb : -nb);
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

	len = ft_strlen(str);
	i = 0;
	print.width = (print.minus ? print.width : print.width - len);
	if (print.minus)
	{
		while (i < len)
		{
			write(1, str, 1);
			i++;
			print.width--;
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
		while (print.width > 0)
		{
			if (print.zero)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			print.width--;
			g_count++;
		}
		while (i < len)
		{
			write(1, str, 1);
			i++;
			g_count++;
		}
	}
}