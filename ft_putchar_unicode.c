/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_unicode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:06:21 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/15 22:31:43 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    ft_unicode(unsigned int c)
{
	int n;
	char ch[4];

    if (c < 128)
    {
		ch[0] = c;
        write(1, ch, 1);
    }
	else if (c < 2048)
    {
		ch[1] = (c >> 6) + 0xC0;
    	ch[0] = (c & 0x3F) + 0x80;
   		write(1, ch, 2);
	}
	else if (c < 65536)
	{
		ch[0] = (c >> 12) + 0xE0;
    	ch[1] = (c & 0x3F) + 0x80;
		ch[2] = ((c >> 6) & 0x3F) + 0x80;
		write(1, ch, 3);
	}
	else if (c < 1114111)
	{
		ch[0] = (c >> 18) + 0xF0;
		ch[1] = ((c >> 12) & 0x3F) + 0x80;
    	ch[2] = ((c >> 6) & 0x3F) + 0x80;
		ch[3] = (c & 0x3F) + 0x80;
		write(1, ch, 4);
	}
}

int main()
{
	ft_unicode(127777);
	ft_unicode('\n');
	return (0);
}