/**
 * @file array.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "alloc.h"
#include "define.h"

void print_array(const char **array)
{
    for (size_t i = INIT; array[i] != NULL; i++) {
        dprintf(STDOUT_FILENO, "{%s} -> ", array[i]);
    }
    dprintf(STDOUT_FILENO, "NULL\n");
}

char **str_to_word_array(char *buffer, const char *delim)
{
    char *cpy = strdup(buffer);
    char **array = (char **) init_pointer(sizeof(char *) * (strlen(cpy) + 1));
    char *token = NULL;
    int i = 0;

    if (array == NULL)
        return NULL;
    token = strtok(cpy, delim);
    while (token != NULL) {
        array[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    array[i] = NULL;
    free(cpy);
    return array;
}

char *buffer_emplace_str(size_t number_str, ...)
{
    char *buffer = NULL;
    va_list ap;

    va_start(ap, number_str);
    for (size_t i = INIT; i < number_str; i++) {
        char *ptr = va_arg(ap, char *);
        buffer = realloc(buffer, strlen(buffer == NULL ? "" : buffer) + strlen(ptr == NULL ? "" : ptr) + 1);
        if (buffer == NULL)
            return NULL;
        i == 0 ? strcpy(buffer, ptr) : strcat(buffer, ptr);
    }
    va_end(ap);
    return buffer;
}

size_t length_array(char **array)
{
    size_t cnt = INIT;

    for (size_t i = INIT; array[i] != NULL; i++) {
        cnt++;
    }
    return cnt;
}

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (size_t i = INIT; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
    array = NULL;
}

size_t count_string_in_array(char **array, const char *string)
{
    size_t cnt = INIT;

    for (size_t i = INIT; i < length_array(array); i++) {
        if (strcmp(array[i], string) == EXIT_SUCCESS)
            cnt++;
    }
    return cnt;
}
