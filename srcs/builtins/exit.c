/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** exit
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "array.h"
#include "define.h"
#include "shell.h"

static int exit_error_handling(size_t len, const char *str)
{
    if (isalpha(str[0]) != false)
        PRINT(STDERR_FILENO, EXIT_FAILURE, EXIT_EXPRESSION_SYNTAX);
    for (size_t i = 0; i < strlen(str); i++) {
        if (isalpha(str[i]) != false)
            PRINT(STDERR_FILENO, EXIT_FAILURE, EXIT_BADLY_FORMED_NUM);
    }
    if (len >= 2)
        PRINT(STDERR_FILENO, EXIT_FAILURE, EXIT_EXPRESSION_SYNTAX);
    return EXIT_SUCCESS;
}

int exit_builtin(const char **argv, shell_t *shell)
{
    size_t len = length_array(argv);

    if (len >= 1) {
        if (exit_error_handling(len, argv[0]) == EXIT_FAILURE)
            return EXIT_FAILURE;
        shell->_exit = atoll(argv[0]);
    }
    shell->_is_exit = true;
    return EXIT_SUCCESS;
}
