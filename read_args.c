#include "monitoring.h"
#include <stdlib.h>

void split_line(char *file)
{
	char **str;
	str = (char **)malloc(sizeof(str));

	str = ft_split(file, '\t');
	config_http(str);
}


