NAME	=	server
CC	=	gcc

CFLAGS	=	-Wall -Wextra -g
CFLAGS	+=	-I./include

SRCS	=	src/server.c \
		src/utils.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
