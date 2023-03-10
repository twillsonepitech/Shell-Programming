/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL : Ubuntu]
** File description:
** where
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "array.h"
#include "define.h"
#include "shell.h"
#include "path.h"

int find_path(const char *path, list_t **environ)
{
    char **path_prefix = str_to_word_array(my_getenv("PATH", environ), ":");

    if (path_prefix == NULL)
        return EXIT_FAILURE_EPI;
    for (size_t i = INIT; i < length_array((const char **) path_prefix); i++) {
        char *absolute_path = buffer_emplace_str(3, path_prefix[i], "/", path);
        if (absolute_path == NULL)
            return EXIT_FAILURE_EPI;
        if (access(absolute_path, X_OK) == EXIT_SUCCESS) {
            dprintf(STDOUT_FILENO, "%s\n", absolute_path);
        }
        free(absolute_path);
    }
    free_array(path_prefix);
    return EXIT_SUCCESS;
}

int where_builtin(char **argv, shell_t *shell)
{
    size_t len = length_array((const char **) argv);

    if (len == 0)
        PRINT(STDERR_FILENO, EXIT_FAILURE, WHERE_FEW_ARGUMENTS);
    for (size_t i = INIT; i < len; i++) {
        if (is_required_builtins(argv[i]) == true)
            dprintf(STDOUT_FILENO, "%s is a shell built-in\n", argv[i]);
        if (find_path(argv[i], &shell->_environ) == EXIT_FAILURE_EPI)
            return EXIT_FAILURE_EPI;
    }
    return EXIT_SUCCESS;
}
