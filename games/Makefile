##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

CC		=	g++

RM		=	rm -rf

NIB		=	nibbler/

FOX		=	solar_fox/

INC		=	-Iinclude/	-I../core/include/

NSRC	=	$(addprefix $(NIB), Nibbler.cpp \
			)

FSRC	=	$(addprefix $(FOX), main.cpp \
			)

NOBJ	=	$(NSRC:.cpp=.o)

FOBJ	=	$(FSRC:.cpp=.o)

FLAG	=	-W -Wall -Wextra

NNAME	=	lib_arcade_nibbler.so

FNAME	=	lib_arcade_solarfox.so

NAME	=	games

all:	$(NAME)

$(NAME):	$(NOBJ)	$(FOBJ)
	$(CC) -shared -o $(NNAME) $(NOBJ)
	$(CC) -shared -o $(FNAME) $(FOBJ)

%.o:	%.cpp
	$(CC) -fpic $(FLAG) $(INC) -o $@ -c $<

clean:
	$(RM) $(NOBJ)
	$(RM) $(FOBJ)

fclean:	clean
	$(RM) $(NNAME)
	$(RM) $(FNAME)

re: fclean all

.PHONY: all clean fclean re