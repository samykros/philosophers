NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -pthread -g

SRCS	=	philo.c \
			init.c \
			utils.c \
			loop.c \
			philosopher_routine.c \
			monitor.c \

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re