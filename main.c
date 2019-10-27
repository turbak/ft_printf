#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	int i;
	char *s;

	s = "123";
	//ft_printf("%C", 1065);
	printf("%.20f\n",        1.025978542436587568678);
	ft_printf("%.20f\n",        1.025978542436587568678);
	//printf("[%d]\n", ft_printf("[%ls]", L"sd"));
	//printf("{%d}", printf("{%ls}", L"sd"));
	return (0);
}
