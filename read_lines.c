#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include  "../libft/libft.h"
#include	"monitoring.h"


void read_lines(t_p *p)
{
	char	*line;
	char *path_to_file = "monitoring.db";
	int  fd;

	fd = open(path_to_file, O_RDONLY);
	line = get_next_line(fd);
	while (!line)
	{
		free(line);
		break ;
	}
	p->header = line;
	line = get_next_line(fd);
	line = get_next_line(fd);
	p->line_one = line;
	line = get_next_line(fd);
	p->line_two = line;
	line = get_next_line(fd);
	p->line_three = line;
	close(fd);
}