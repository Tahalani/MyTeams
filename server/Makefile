##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## Makefile
##

SRC			=	src/commands/auth.c \
				src/commands/channel.c \
				src/commands/info.c \
				src/commands/interaction.c \
				src/commands/message.c \
				src/commands/subscribe.c \
				src/commands/subscribed.c \
				src/commands/unsubscribe.c \
				src/commands/talk.c \
				src/commands/team.c \
				src/commands/thread.c \
				src/commands/use.c \
				src/commands/user.c \
				src/core/cache.c \
				src/core/commands.c \
				src/core/data.c \
				src/core/fdsets.c \
				src/core/init.c \
				src/core/loop.c \
				src/core/packets.c \
				src/database/channel.c \
				src/database/channel_rel.c \
				src/database/entry.c \
				src/database/message.c \
				src/database/team.c	\
				src/database/team_rel.c	\
				src/database/thread.c \
				src/database/thread_rel.c \
				src/database/user.c	\
				src/database/utils.c \
				src/objects/channels.c \
				src/objects/clients.c \
				src/objects/messages.c \
				src/objects/teams.c \
				src/objects/threads.c \
				src/objects/users.c \
				src/util/arrays.c \
				src/util/checks.c \
				src/util/context.c \
				src/util/util.c \
				src/server.c

MAIN		=	src/main.c

INC			=	include/

NAME		=	myteams_server

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
