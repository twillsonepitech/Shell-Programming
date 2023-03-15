/**
 * @file env.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
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

int env_builtin(char **argv, shell_t *shell)
{
    if (length_array((const char **) argv) != 0)
        PRINT(STDERR_FILENO, EXIT_FAILURE, ENV_ARGUMENTS, argv[0]);
    print_env(&shell->_environ);
    return EXIT_SUCCESS;
}
