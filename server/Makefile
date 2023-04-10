##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## Makefile
##

SRC			=	src/commands/auth.c \
				src/commands/talk.c \
				src/commands/user.c \
				src/commands/subscribe.c \
				src/commands/use.c \
				src/commands/interaction.c \
				src/commands/team.c \
				src/commands/channel.c \
				src/commands/thread.c \
				src/commands/reply.c \
				src/core/commands.c \
				src/core/fdsets.c \
				src/core/loop.c \
				src/core/packets.c \
				src/util/arrays.c \
				src/util/clients.c \
				src/util/data.c \
				src/util/getters.c \
				src/util/getters2.c \
				src/util/messages.c \
				src/util/util.c \
				src/server.c \

MAIN		=	src/main.c

INC			=	include/

NAME		=	myteams_server

OBJ			=	$(SRC:.c=.o)
OBJ_M 		=	$(MAIN:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra
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
