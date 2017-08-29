NAME	=	./client
CC	=	gcc

CFLAGS	=	-Wall -Wextra -g
CFLAGS	+=	-I./include

SRCS	=	src/main.c

OBJS	=	$(SRCS:.cpp=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
