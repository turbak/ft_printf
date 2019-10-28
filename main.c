#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	char *s;

	s = "123";
	//ft_printf("%C", 1065);
	//printf("%.0f\n", 0.000039);
	ft_printf("%S", L"Поставь 100 плз, я хочу умереть");
	//printf("[%d]\n", ft_printf("[%ls]", L"sd"));
	//printf("{%d}", printf("{%ls}", L"sd"));
	return (0);
}
