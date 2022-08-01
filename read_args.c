#include "monitoring.h"
#include <stdlib.h>

int main ()
{
	t_p p;
	char **str;

	read_lines(&p);
	str = (char **)malloc(sizeof(str));
	while (p.line_one)
	{
		str = ft_split(p.line_one, '\t');
		if (ft_strncmp(str[1], "HTTP", 4) == 0)
			config_http(str);          
	}
	while (p.line_two)
	{
		str = ft_split(p.line_two, '\t');
		if (ft_strncmp(str[1], "HTTP", 4) == 0)
			config_http(str);
	}
	while (p.line_three)
	{
		str = ft_split(p.line_three, '\t');
		if (ft_strncmp(str[1], "HTTP", 4) == 0)
			config_http(str);
	}
	
	//printf("Arg.one: %s\n", arg->one);
	//printf("Arg.two: %s", arg->two);
}
