##
## EPITECH PROJECT, 2022
## base_projet
## File description:
## Makefile
##

EXT_CRI		=		*.gcno *.gcda

EXTENSION	=		.c

SRC			=		$(addsuffix .c, $(addprefix src/,		\
					projet									\
					main))									\

SRCT		=		tests/tests_projet$(EXTENSION)			\
					$(addsuffix .c, $(addprefix src/,		\
					cesar))									\

OBJ			=		$(SRC:$(EXTENSION)=.o)

OBJT		=		$(SRCT:$(EXTENSION)=.o)

CPPFLAGS	=		-Wall -Wextra

CFLAGS		=		-I./includes

LDFLAGS		=		-L./lib/my -lmy

TEST_FLAG	=		-lcriterion --coverage

CC			=		gcc

MKU			=		mkdir $(NAME_DIR)

MV			=		mv

NAME		=		projet

NAME_CRI	=		units_tests

NAME_DIR	=		unwanted

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C lib/my
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@echo -e "\e[92;5m----- PROJECT START -----\e[0m"

clean:
	$(RM) $(OBJ)
	@echo -e "\e[35m----- PROJECT CLEANED -----\033[0m"

fclean: clean
	$(MAKE) -C lib/my fclean
	$(RM) $(NAME)
	$(RM) $(NAME_CRI)
	$(RM) -r $(NAME_DIR)
	$(RM) $(OBJT)
	$(RM) $(EXT_CRI)

re:		fclean all

units_tests:	fclean $(OBJT)
	$(MAKE) -C lib/my
	$(CC) -o $(NAME_CRI) $(SRCT) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TEST_FLAG)
	-L./lib/my -lmy
	$(MKU)
	$(MV) *.gcno $(NAME_DIR)

tests_run:		units_tests
	./$(NAME_CRI)
	$(MV) *.gcda $(NAME_DIR)
	gcovr $(NAME_DIR)/

debug: CPPFLAGS += -g3
debug: re

.PHONY: all re clean fclean units_tests tests_run debug
