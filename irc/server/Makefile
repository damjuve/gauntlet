NAME	=	server
CC	=	gcc

CFLAGS	=	-Wall -Wextra -g
CFLAGS	+=	-I./include

SRCS	=	src/server.c \
		src/utils.c  \
		src/client.c \
		src/msg.c \
		src/command.c \
		src/remove_client.c \
		src/debug.c \
		src/channel.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
