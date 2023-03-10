/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** builtins
*/

#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "shell.h"

bool is_required_builtins(const char *cmd)
{
    for (size_t i = INIT; i < sizeof(builtins) / sizeof(builtins[0]); i++) {
        if (strcmp(builtins[i], cmd) == EXIT_SUCCESS)
            return true;
    }
    return false;
}

int execute_builtins(const char *cmd, char **argv, shell_t *shell)
{
    for (size_t i = INIT; i < sizeof(BUILTINS) / sizeof(BUILTINS[0]); i++) {
        if (strcmp(BUILTINS[i]._builtin, cmd) == EXIT_SUCCESS)
            return BUILTINS[i]._builtin_ptr(argv, shell);
    }
    return EXIT_SUCCESS;
}
