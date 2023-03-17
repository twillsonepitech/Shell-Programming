/**
 * @file array.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <sys/types.h>

char **str_to_word_array(char *buffer, const char *delim);
char *buffer_emplace_str(size_t number_str, ...);
size_t length_array(char **array);
void free_array(char **array);
void print_array(char **array);
size_t count_string_in_array(char **array, const char *string);

#endif /* !ARRAY_H_ */
