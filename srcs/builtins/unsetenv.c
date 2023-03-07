/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** unsetenv
*/

#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "define.h"
#include "shell.h"

static void handle_unsetenv(const char *key, list_t **list)
{
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        if (strcmp(tmp->_key, key) == EXIT_SUCCESS) {
            free_list_by_key(list, key);
            return ;
        }
    }
    return ;
}

int unsetenv_builtin(const char **argv, shell_t *shell)
{
    if (length_array(argv) == 0)
        PRINT(STDERR_FILENO, EXIT_FAILURE, UNSETENV_FEW_ARGUMENTS);
    for (int i = 0; argv[i] != NULL; i++) {
        handle_unsetenv(argv[i], &shell->_list);
    }
    return EXIT_SUCCESS;
}
