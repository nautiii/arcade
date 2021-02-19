##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

CC		=	g++

RM		=	rm -rf

AA		=	libaa/

CACA	=	libcaca/

SFML	=	libsfml/

INC		=	-Iinclude/ -I../core/include/

ASRC	=	$(addprefix $(AA), IAaLib.cpp \
			)

CSRC	=	$(addprefix $(CACA), ILibCaca.cpp \
			)

SSRC	=	$(addprefix $(SFML), ISfml.cpp \
			)

AOBJ	=	$(ASRC:.cpp=.o)

COBJ	=	$(CSRC:.cpp=.o)

SOBJ	=	$(SSRC:.cpp=.o)

FLAG	=	-W -Wall -Wextra

AFLAG	=	-laa

CFLAG	=	-lcaca

SFLAG	=	-lsfml-graphics -lsfml-window -lsfml-system

ANAME	=	lib_arcade_aa-lib.so

CNAME	=	lib_arcade_libcaca.so

SNAME	=	lib_arcade_sfml.so

NAME	=	lib

all:	$(NAME)

$(NAME):	$(AOBJ)	$(COBJ) $(SOBJ)
	$(CC) -shared $(AFLAG) -o $(ANAME) $(AOBJ)
	$(CC) -shared $(CFLAG) -o $(CNAME) $(COBJ)
	$(CC) -shared $(SFLAG) -o $(SNAME) $(SOBJ)

%.o:	%.cpp
	$(CC) -c -fpic $(FLAG) $(INC) $< -o $@ 

clean:
	$(RM) $(AOBJ)
	$(RM) $(COBJ)
	$(RM) $(SOBJ)

fclean:	clean
	$(RM) $(ANAME)
	$(RM) $(CNAME)
	$(RM) $(SNAME)

re: fclean all

.PHONY: all clean fclean re