/**
 * @file handle_env.c
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
#include "alloc.h"
#include "array.h"
#include "define.h"
#include "shell.h"

static size_t my_strlen_c(const char *buffer, const char c)
{
    size_t cnt = INIT;

    for (size_t i = INIT; buffer[i] != c; i++) {
        cnt++;
    }
    return cnt;
}

static void buffer_emplace_back(const char *str, char **buffer, const char c)
{
    for (size_t i = INIT; str[i] != c; i++) {
        (*buffer)[i] = str[i];
    }
}

static int get_key_value(const char *dup, char **key, char **value)
{
    size_t key_length = my_strlen_c(dup, '=');

    *key = (char *) init_pointer(sizeof(char) * (key_length + 1));
    if (*key == NULL)
        return EXIT_FAILURE_EPI;
    buffer_emplace_back(dup, key, '=');
    *value = strdup(dup + key_length + 1);
    if (*value == NULL)
        return EXIT_FAILURE_EPI;
    return EXIT_SUCCESS;
}

int handle_environment(char **env, shell_t *shell)
{
    char *key = NULL;
    char *value = NULL;

    for (size_t i = INIT; i < length_array(env); i++) {
        if (get_key_value(env[i], &key, &value) == EXIT_FAILURE_EPI)
            return EXIT_FAILURE_EPI;
        if (list_add_node(&shell->_environ, key, value) == false)
            return EXIT_FAILURE_EPI;
        free(key);
        free(value);
    }
    return EXIT_SUCCESS;
}
