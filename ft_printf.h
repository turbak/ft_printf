/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:30 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 19:58:50 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	g_count;

typedef struct 	g_flags
{
	char		flag;
	char		zero;
	char		hash;
	char		minus;
	char		plus;
	char		space;
	int			width;
	int			precision;
	char		size;
	char		type;
	int			index;
}				t_flags;

int		ft_printf(const char *format, ...);
char	*base_10_trans(unsigned int n, int base);
void	base_16_trans(int n, int up, t_flags print);
void	ft_putaddr(int n, int up, t_flags print);
void	ft_putchar(char c);
void	ft_putnbr_unsigned(unsigned int n);
void	ft_putnbr(int n);
void	ft_putstr(char const *s);
size_t	ft_strlen(const char *s);
char	*ft_strnew(size_t size);
char	*ft_strrev(char *s);
int		ft_atoi(const char *str);
char		*ft_itoa(int n);
void	put_int(char *str, t_flags print);
t_flags init_print();
void	put_int_unsigned(char *str, t_flags print);
char	*ft_itoa_unsigned(unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_swapfree(void **ptr, void *ptr2);

#endif