/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** setenv
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "array.h"
#include "define.h"
#include "shell.h"

static int setenv_error_handling(size_t len, const char *str)
{
    if (len >= 3)
        PRINT(STDERR_FILENO, EXIT_FAILURE, SETENV_MANY_ARGUMENTS);
    if (isalpha(str[0]) == false)
        PRINT(STDERR_FILENO, EXIT_FAILURE, SETENV_BEGIN_LETTER);
    for (size_t i = INIT; i < strlen(str); i++) {
        if (isalnum(str[i]) == false)
            PRINT(STDERR_FILENO, EXIT_FAILURE, SETENV_CONTAIN_ALNUM);
    }
    return EXIT_SUCCESS;
}

bool inside_environment(const char *key, const char *value, list_t **list)
{
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        if (strcmp(tmp->_key, key) == EXIT_SUCCESS) {
            free(tmp->_value);
            tmp->_value = strdup(value);
            return true;
        }
    }
    return false;
}

static int handle_setenv(const char *key, const char *value, list_t **list)
{
    if (list_add_node(list, key, value) == false)
        return EXIT_FAILURE_EPI;
    return EXIT_SUCCESS;
}

int setenv_builtin(char **argv, shell_t *shell)
{
    size_t len = length_array((const char **) argv);

    if (len == 0) {
        print_env(&shell->_environ);
        return EXIT_SUCCESS;
    }
    if (setenv_error_handling(len, argv[0]) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (inside_environment(argv[0], argv[1] == NULL ? "" : argv[1], &shell->_environ) != true) {
        if (handle_setenv(argv[0], argv[1] == NULL ? "" : argv[1], &shell->_environ) == EXIT_FAILURE_EPI) {
            return EXIT_FAILURE_EPI;
        }
    }
    return EXIT_SUCCESS;
}
