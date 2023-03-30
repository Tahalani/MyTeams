##
## EPITECH PROJECT, 2021
## makfile
## File description:
## compile
##

LIB	=	my_compute_power_rec.c		\
		my_compute_square_root.c	\
		my_strdup.c					\
		my_find_prime_sup.c			\
		my_getnbr.c					\
		my_memset.c					\
		my_char_isnum.c				\
		my_isneg.c					\
		my_is_prime.c				\
		my_putchar.c				\
		my_put_nbr.c				\
		my_putstr.c					\
		my_revstr.c					\
		my_strcapitalize.c			\
		my_strcat.c					\
		my_strcmp.c					\
		my_strcpy.c					\
		my_str_isalpha.c			\
		my_str_islower.c			\
		my_str_isnum.c				\
		my_str_isprintable.c		\
		my_str_isupper.c			\
		my_strlen.c					\
		my_strlowcase.c				\
		my_strncat.c				\
		my_strncmp.c				\
		my_strncpy.c				\
		my_strupcase.c				\
		my_swap.c					\
		my_file_in_str.c			\
		my_str_to_word_array.c		\
		my_free_array.c				\
		my_create_array.c			\
		my_put_array.c				\
		my_len_cmp.c

OBJL		=		$(LIB:.c=.o)

CPPFLAGS	=		-Wall -Wextra -g3

CFLAGS		=		-Iincludes	$(LDFLAGS)

AR			=		@ar rc

RM			=		rm -f

NAME		=		libmy.a

all:	$(NAME)

.SILENT:

$(NAME):	$(OBJL)
	@$(AR) $(NAME) $(OBJL)
	@cp $(NAME) ../
	@cp my.h ../../includes/

clean:
	@$(RM) $(OBJL)

fclean:
	@$(RM) $(OBJL)
	@$(RM) $(NAME)
	@$(RM) ../$(NAME)

re:	fclean	all
