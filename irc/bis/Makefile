##
## Makefile for Makefile in /home/abrun/delivery/Tek2/PSU/PSU_2016_myirc
## 
## Made by Alexandre Brun
## Login   <abrun@epitech.net>
## 
## Started on  Tue May 23 10:52:49 2017 Alexandre Brun
## Last update Sun Jun 11 19:56:42 2017 Alexandre Brun
##

CC		=	gcc

RM		=	rm -f

CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-I include/

SERVER_NAME	=	server

CLIENT_NAME	=	client

SERVER_SRC	=	src/server.c		\
			src/utils.c		\
			src/my_str_to_wordtab.c	\
			src/users.c		\
			src/channels.c		\
			src/getters.c		\
			src/setters.c		\
			src/commands_server.c	\
			src/write_functions.c

CLIENT_SRC	=	src/client.c		\
			src/my_str_to_wordtab.c	\
			src/commands_client.c	\
			src/get_next_line.c

SERVER_OBJS	=	$(SERVER_SRC:.c=.o)

CLIENT_OBJS	=	$(CLIENT_SRC:.c=.o)


all	:		server client

server	:		$(SERVER_OBJS)
			$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) $(CFLAGS)


client	:		$(CLIENT_OBJS)
			$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(CFLAGS)
clean	:
			$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)

fclean	:		clean
			$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re	:		fclean all

.PHONY	:		all clean fclean re server
