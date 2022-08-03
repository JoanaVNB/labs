#ifndef MONITORING_H
# define MONITORING_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include  "../libft/libft.h"

void read_lines(int fd);
void config_http(char **str);
void split_line_http(char *file);
void config_ping(char **str);
void split_line_ping(char *file);
void config_dns(char **str);
void split_line_dns(char *file);
#endif

