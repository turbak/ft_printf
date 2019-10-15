/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_transfer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:45:09 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/15 17:04:22 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*base_10_trans(unsigned int n, int base, t_flags print)
{
	char			*str;
	unsigned int 	i;
	int				len;

	i = n;
	len = 0;
	if (!n)
		return (print.hash || !(print.dot && !print.precision) ? "0" : "");
	while (i != 0)
	{
		i /= base;
		++len;
	}
	i = 0;
	str = ft_strnew(len);
	while (n != 0)
	{
		str[i++] = '0' + n % base;
		n /= base;
	}
	if (print.hash)
		ft_swapfree((void**)&str, ft_strjoin(str, "0"));
	ft_strrev(str);
	return (str);
}

char	*base_16_trans(uintmax_t n, int up, t_flags print)
{
	char			*str;
	uintmax_t 	i;
	uintmax_t	len;

	if (!n)
		return ((print.hash && print.precision) || !(print.dot && !print.precision) ? "0" : "");
	i = n;
	len = 0;
	while (i != 0)
	{
		i /= 16;
		++len;
	}
	i = 0;
	str = ft_strnew(len);
	while (n != 0)
	{
		len = n % 16;
		if (len < 10)
			str[i++] = '0' + n % 16;
		else if (len == 10)
			str[i++] = (up ? 'A' : 'a');
		else if (len == 11)
			str[i++] = (up ? 'B' : 'b');
		else if (len == 12)
			str[i++] = (up ? 'C' : 'c');
		else if (len == 13)
			str[i++] = (up ? 'D' : 'd');
		else if (len == 14)
			str[i++] = (up ? 'E' : 'e');
		else if (len == 15)
			str[i++] = (up ? 'F' : 'f');
		n /= 16;
	}
	ft_strrev(str);
	if (print.hash)
		ft_swapfree((void**)&str, ft_strjoin((up ? "0X" : "0x"), str));
	return (str);
}

void	ft_putaddr(int n, int up, t_flags print)
{
	char			*str;
	unsigned int 	i;
	unsigned int	len;

	i = n;
	len = 0;
	while (i != 0)
	{
		i /= 16;
		++len;
	}
	i = 0;
	str = ft_strnew(len);
	while (n != 0)
	{
		len = n % 16;
		if (len < 10)
			str[i++] = '0' + n % 16;
		else if (len == 10)
			str[i++] = (up ? 'A' : 'a');
		else if (len == 11)
			str[i++] = (up ? 'B' : 'b');
		else if (len == 12)
			str[i++] = (up ? 'C' : 'c');
		else if (len == 13)
			str[i++] = (up ? 'D' : 'd');
		else if (len == 14)
			str[i++] = (up ? 'E' : 'e');
		else if (len == 15)
			str[i++] = (up ? 'F' : 'f');
		n /= 16;
	}
	ft_swapfree((void**)&str, ft_strjoin(str, "0x10"));
	put_int_unsigned(str, print, '0');
}