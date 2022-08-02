NAME		= monitoring
CC			= clang
CFLAGS		= -Wall -Wextra -Werror

LIBFT	= libft.a
IFT		= -Ilibft -Llibft -lft
ICURL = -lcurl

SRCS	= main.c read_lines.c read_args.c config_http.c

OBJSDIR	= obj
OBJS	= $(addprefix ${OBJSDIR}/, ${SRCS:%.c=%.o})
B_OBJS	= $(addprefix ${OBJSDIR}/, ${B_SRCS:%.c=%.o})

all: ${NAME}

${NAME}: ${SRCS}
	${CC} ${CFLAGS} -g ${SRCS} ${IFT} ${ICURL} -o ${NAME}

${OBJSDIR}:
	mkdir -p $@

${OBJS}: | ${LIBFT} 
${B_OBJS}: | ${LIBFT} 

${OBJSDIR}/%.o: src/%.c monitoring.h
	${CC} ${CFLAGS} -c $< -o $@

run:
	./$(NAME)

valgrind:
	valgrind --leak-check=full ./$(NAME) 

${LIBFT}: | libft
	${MAKE} -C libft/

clean:
	${MAKE} clean -C libft
	rm -rf ${OBJSDIR}
	
fclean: clean
	rm -rf ${NAME}

re: fclean all