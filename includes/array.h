/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** array
*/

#ifndef ARRAY_H_
#define ARRAY_H_

#include <sys/types.h>

char **str_to_word_array(char *buffer, const char *delim);
char *buffer_emplace_str(size_t number_str, ...);
size_t length_array(const char **array);
void free_array(char **array);
void print_array(const char **array);
size_t count_string_in_array(const char **array, const char *string);

#endif /* !ARRAY_H_ */
