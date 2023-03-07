/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** array
*/

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "alloc.h"

char **str_to_word_array(char *buffer, const char *delim)
{
    char **array = (char **) init_pointer(sizeof(char *) * (strlen(buffer) + 1));
    char *token = NULL;
    int i = 0;

    if (array == NULL)
        return NULL;
    token = strtok(buffer, delim);
    while (token != NULL) {
        array[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    array[i] = NULL;
    return array;
}

char *buffer_emplace_str(size_t number_str, ...)
{
    char *buffer = NULL;
    va_list ap;

    va_start(ap, number_str);
    for (size_t i = 0; i < number_str; i++) {
        char *ptr = va_arg(ap, char *);
        buffer = realloc(buffer, strlen(buffer == NULL ? "" : buffer) + strlen(ptr == NULL ? "" : ptr) + 1);
        if (buffer == NULL)
            return NULL;
        i == 0 ? strcpy(buffer, ptr) : strcat(buffer, ptr);
    }
    va_end(ap);
    return buffer;
}

size_t length_array(const char **array)
{
    size_t cnt = 0;

    for (int i = 0; array[i] != NULL; i++) {
        cnt++;
    }
    return cnt;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}
