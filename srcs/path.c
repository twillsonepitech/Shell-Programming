/**
 * @file path.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "define.h"
#include "list.h"

char *my_getenv(const char *key, list_t **list)
{
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        if (strcmp(tmp->_key, key) == EXIT_SUCCESS)
            return tmp->_value;
    }
    return NULL;
}

char *get_absolute_path(const char *path, list_t **list)
{
    char **path_prefix = str_to_word_array(my_getenv("PATH", list), ":");

    if (path_prefix == NULL)
        return NULL;
    for (size_t i = INIT; i < length_array((const char **) path_prefix); i++) {
        char *absolute_path = buffer_emplace_str(3, path_prefix[i], "/", path);
        if (absolute_path == NULL)
            return NULL;
        if (access(absolute_path, X_OK) == EXIT_SUCCESS) {
            free_array(path_prefix);
            return absolute_path;
        }
        free(absolute_path);
    }
    free_array(path_prefix);
    return strdup(path);
}

int get_working_directory(char path[PATH_MAX])
{
    if (getcwd(path, PATH_MAX) == NULL)
        return EXIT_FAILURE_EPI;
    return EXIT_SUCCESS;
}
