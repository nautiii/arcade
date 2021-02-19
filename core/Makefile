##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

CC		=	g++

RM		=	rm -rf

DIR		=	src/

INC		=	-Iinclude/ -I../core/include/

SRC		=	$(addprefix $(DIR), main.cpp \
								ErrorHandling.cpp \
								Storage.cpp \
								Core.cpp \
			)

OBJ		=	$(SRC:.cpp=.o)

FLAG	=	-W -Wall -Wextra -std=c++17

NAME	=	arcade

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -ldl -lstdc++fs -o $@
	mv $@ ..

%.o:	%.cpp
	$(CC) $(FLAG) $(INC) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re