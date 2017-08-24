NAME	=	gauntlet
CC	=	g++

LDFLAGS		=	-L./lib -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor
CPPFLAGS	=	-Wall -Wextra -std=c++11 -g
CPPFLAGS	+=	-I./include -I./lib/include

SRCS	=	src/main.cpp \
		src/Game.cpp \
		src/Exceptions.cpp \
		src/AEnnemy.cpp \
		src/ACharacter.cpp \
		src/AEntity.cpp \
		src/Map.cpp \
		src/Sydney.cpp \
		src/Faerie.cpp \
		src/Ninja.cpp \
		src/Dwarf.cpp \
		src/APlayer.cpp \
		src/AProjectile.cpp \
		src/Camera.cpp \
		src/Mob.cpp \
		src/Tile.cpp \
		src/Fireball.cpp \
		src/Sword.cpp \
		src/Shuriken.cpp \
		src/Axe.cpp \
		src/Boss.cpp

OBJS	=	$(SRCS:.cpp=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
