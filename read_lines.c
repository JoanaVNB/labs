#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include  "../libft/libft.h"
#include	"monitoring.h"

void read_lines(int fd)
{
	char	*temp;
	char	*line;
	char	*buffer;
	char	**file;
	int	x;

	x = 0;
	buffer = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		temp = buffer;
		buffer = ft_strjoin(temp, line);
		free(line);
		free(temp);
	}
	file = ft_split(buffer, '\n');
	free(buffer);
	while (file[x])
	{
		if (strstr(file[x], "HTTP") != 0)
			split_line(file[x]);
		x++;
	}
}