##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## Makefile
##

SRC			=	../cli/src/cli.c \
				../server/src/server.c

TEST		=	unit_tests
TESTS		=	test_server.c

TEST_GCDA	=	$(SRC:.c=.gcda) \
				$(TESTS:.c=.gcda)
TEST_GCNO	=	$(SRC:.c=.gcno) \
				$(TESTS:.c=.gcno)

OBJ			=	$(SRC:.c=.o)
OBJ_T		=	$(TESTS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Wpedantic --coverage
CPPFLAGS	=	-iquote ../cli/include/ -iquote ../server/include/
TESTFLAGS	=	--coverage -lcriterion $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_T)
	$(RM) $(TEST_GCDA)
	$(RM) $(TEST_GCNO)

fclean: clean
	$(RM) $(TEST)

tests_run: clean $(OBJ) $(OBJ_T)
	$(CC) -o $(TEST) $(OBJ) $(OBJ_T) $(TESTFLAGS)
	./$(TEST)

.PHONY: clean tests_run
