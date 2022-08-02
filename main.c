#include "monitoring.h"
#include <stdlib.h>

int main ()
{
	char *path_to_file = "monitoring.db";
  int fd;

	fd = open(path_to_file, O_RDONLY);
	read_lines(fd);
	close(fd);
}
