#include "monitoring.h"

void split_line_http(char *file)
{
	char **str;
	
	str = ft_split(file, '\t');
	config_http(str);
}

void split_line_ping(char *file)
{
	char **str;
	
	str = ft_split(file, '\t');
	config_ping(str);
}

void split_line_dns(char *file)
{
	char **str;

	str = ft_split(file, '\t');
	config_dns(str);
}


