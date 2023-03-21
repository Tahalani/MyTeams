##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## Makefile
##

all: server cli

clean:
	$(MAKE) -C server/ clean
	$(MAKE) -C cli/ clean
	$(MAKE) -C tests/ clean

cli:
	$(MAKE) -C cli/

debug:
	$(MAKE) -C server/ debug
	$(MAKE) -C cli/ debug

fclean:
	$(RM) myteams_cli myteams_server
	$(MAKE) -C server/ fclean
	$(MAKE) -C cli/ fclean
	$(MAKE) -C tests/ fclean

re:
	$(MAKE) -C server/ re
	$(MAKE) -C cli/ re

server:
	$(MAKE) -C server/

tests_run:
	$(MAKE) -C tests/ tests_run

.PHONY: all clean cli debug fclean re server tests_run
