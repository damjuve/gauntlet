NAME	=	irc
CC	=	gcc

CLIENT_DIR = ./client
SERVER_DIR = ./server

CLIENT_NAME = client
SERVER_NAME = server

CLIENT	:	make -C CLIENT_DIR
		cp $(CLIENT_DIR)/$(CLIENT_NAME) ./$(CLIENT_NAME)
SERVER	:	make -C SERVER_DIR
		cp $(SERVER_DIR)/$(SERVER_NAME) ./$(SERVER_NAME)

all	:	CLIENT SERVER

clean	:
		make -C $(CLIENT_DIR) clean
		make -C $(SERVER_DIR) clean
fclean	:
		make -C $(CLIENT_DIR) fclean
		rm ./$(CLIENT_NAME)
		make -C $(SERVER_DIR) fclean
		rm ./$(SERVER_NAME)

re	:	fclean all
