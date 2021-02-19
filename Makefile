##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

CORE	=	core/

GAMES	=	games/

LIB		=	lib/

NAME	=	global

all:	$(NAME)

$(NAME):
	make -sC $(CORE)
	make -sC $(GAMES)
	make -sC $(LIB)

core:
	make -sC $(CORE)

games:
	make -sC $(GAMES)

graphicals:
	make -sC $(LIB)

clean:
	make clean -sC $(CORE)
	make clean -sC $(GAMES)
	make clean -sC $(LIB)

fclean:	clean
	make fclean -sC $(CORE)
	make fclean -sC $(GAMES)
	make fclean -sC $(LIB)

re: fclean all

.PHONY: all core games graphicals clean fclean re