#ifndef MONITORING_H
# define MONITORING_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include  "../libft/libft.h"

typedef struct s_p
{
  char *header;
  char *line_one;
  char *line_two;
  char *line_three;
} t_p;

/* typedef struct s_arg
{
  char *zero;
  char *one;
  char *two;
  char *three;
  char *four;
  char *five;

} t_arg; */

typedef struct s_http
{
   char *nome;
  char *protocolo;
  char *endereço;
  char *metodo;
  int codigo;
  int intervalo; 
} t_http;

//char *line = 0;
void read_lines(t_p *p);
void trim_word(char *dest, int c, char *str);
int config_http(char **str);

#endif

