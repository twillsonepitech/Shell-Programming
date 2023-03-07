/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** env
*/

#include <stdlib.h>
#include "array.h"
#include "define.h"
#include "shell.h"

void print_env(list_t **list)
{
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        dprintf(STDOUT_FILENO, "%s=%s\n", tmp->_key, tmp->_value);
    }
}

int env_builtin(const char **argv, shell_t *shell)
{
    if (length_array(argv) != 0)
        PRINT(STDERR_FILENO, EXIT_FAILURE, ENV_ARGUMENTS, argv[0]);
    print_env(&shell->_list);
    return EXIT_SUCCESS;
}
