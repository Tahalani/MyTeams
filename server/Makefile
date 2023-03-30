##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## Makefile
##

SRC			=	src/commands/auth.c \
				src/commands/user.c \
				src/clients.c \
				src/commands.c \
				src/fdsets.c \
				src/loop.c \
				src/messages.c \
				src/server.c \
				src/util.c \
				src/str_to_word.c

MAIN		=	src/main.c

INC			=	include/

NAME		=	myteams_server

OBJ			=	$(SRC:.c=.o)
OBJ_M 		=	$(MAIN:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Wpedantic
CPPFLAGS	=	-iquote $(INC) -iquote ../lib/myteams

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_M)
	$(CC) -o $(NAME) $(OBJ) $(OBJ_M)
	cp $(NAME) ../

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_M)

debug: CPPFLAGS += -g3
debug: re

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
