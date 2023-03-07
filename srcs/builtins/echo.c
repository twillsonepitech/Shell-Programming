/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** echo
*/

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "array.h"
#include "shell.h"

int echo_builtin(const char **argv, shell_t *shell)
{
    size_t len = length_array(argv);

    for (size_t i = 0; i < len; i++) {
        strcmp(argv[i], "$?") == EXIT_SUCCESS ? dprintf(STDOUT_FILENO, "%" PRIu32, shell->_echo) : dprintf(STDOUT_FILENO, "%s", argv[i]);
        if (i != len - 1)
            dprintf(STDOUT_FILENO, " ");
    }
    dprintf(STDOUT_FILENO, "\n");
    return EXIT_SUCCESS;
}
