/**
 * @file unsetenv.c
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

int unsetenv_builtin(char **argv, shell_t *shell)
{
    size_t len = length_array(argv);

    if (len == 0)
        PRINT(STDERR_FILENO, EXIT_FAILURE, UNSETENV_FEW_ARGUMENTS);
    for (size_t i = INIT; i < len; i++) {
        handle_unsetenv(argv[i], &shell->_environ);
    }
    return EXIT_SUCCESS;
}
