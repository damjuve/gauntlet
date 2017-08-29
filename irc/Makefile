NAME	=	irc
CC	=	gcc

CLIENT_DIR = client/
SERVER_DIR = server/

CLIENT	:
		make -C $(CLIENT_DIR)
SERVER	:
		make -C $(SERVER_DIR)

all	:	CLIENT SERVER

clean	:
		make -C $(CLIENT_DIR) clean
		make -C $(SERVER_DIR) clean
fclean	:
		make -C $(CLIENT_DIR) fclean
		make -C $(SERVER_DIR) fclean

re	:	fclean all
