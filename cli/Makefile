##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## Makefile
##

SRC			=	src/commands/auth.c \
				src/commands/basic.c \
				src/commands/create.c \
				src/commands/misc.c \
				src/commands/subscribe.c \
				src/commands/use.c \
				src/packets/data.c \
				src/packets/errors.c \
				src/packets/users.c \
				src/packets/send.c \
				src/arrays.c \
				src/cli.c \
				src/client.c \
				src/input.c \
				src/util.c \
				src/parsing.c \

MAIN		=	src/main.c

INC			=	include/

NAME		=	myteams_cli

OBJ			=	$(SRC:.c=.o)
OBJ_M 		=	$(MAIN:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Wpedantic
CPPFLAGS	=	-iquote $(INC) -iquote ../include -iquote ../libs/myteams
LDLIBS		=	-lmyteams
LDFLAGS		=	-L../libs/myteams

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_M)
	$(CC) -o $(NAME) $(OBJ) $(OBJ_M) $(LDFLAGS) $(LDLIBS)
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
