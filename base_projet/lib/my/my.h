/*
** EPITECH PROJECT, 2021
** include
** File description:
** include
*/

#ifndef MY_H_
    #define MY_H_

    #define ATOD(x) (x - '0')
    #define DTOA(x) (x + '0')

char **my_str_to_word_array(char *str, char separator);

char **my_malloc_tab(int nbr_rows);

char *my_strdup(char const *src);

char *my_strupcase(char *str);

char *my_strlowcase(char *str);

char *my_strcapitalize(char *str);

char *my_strncpy(char *dest, char const *src, int n);

char *my_strcat(char *dest, char const *src);

char *my_revstr(char *str);

char *my_strncat(char *dest, char const *src, int nb);

char *my_strconcat(char *dest, char const *src);

char *my_strcpy(char *dest, char const *src);

int my_char_isnum(char a);

int my_isneg(int nb);

int my_strcmp(char const *s1, char const *s2);

int my_put_nbr(int nb);

int my_strncmp(char const *s1, char const *s2, int n);

int my_putstr(char const *str);

int my_strlen(char const *str);

int my_getnbr(char const *str);

int my_str_isalpha(char const *str);

int my_str_isnum(char const *str);

int my_compute_power_rec(int nb, int power);

int my_str_islower(char const *str);

int my_compute_square_root(int nb);

int my_str_isupper(char const *str);

int my_is_prime(int nb);

int my_str_isprintable(char const *str);

int my_find_prime_sup(int nb);

int my_showstr(char const *str);

int my_showmem(char const *str, int size);

int len_cmp(char *str1, char *str2);

void my_putchar(char c);

void my_put_error(char const *str);

void my_swap(int *a, int *b);

void my_free_array(char **array);

void my_put_array(char **array);

char *my_file_in_str(char *filepath);

#endif/* MY_H_ */
