/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** path
*/

#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "array.h"

char *my_getenv(const char *key, char **env)
{
    for (size_t i = 0; i < length_array((const char **) env); i++) {
        if (strncmp(env[i], key, strlen(key)) == EXIT_SUCCESS)
            return &env[i][strlen(key) + 1];
    }
    return NULL;
}

char *get_absolute_path(const char *path, char **env)
{
    char **path_prefix = str_to_word_array(my_getenv("PATH", env), ":");

    if (path_prefix == NULL)
        return NULL;
    for (size_t i = 0; i < length_array((const char **) path_prefix); i++) {
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
