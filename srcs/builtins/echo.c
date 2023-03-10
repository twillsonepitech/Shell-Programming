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
#include "define.h"
#include "path.h"
#include "shell.h"

int echo_builtin(char **argv, shell_t *shell)
{
    size_t len = length_array((const char **) argv);

    for (size_t i = INIT; i < len; i++) {
        if (strcmp(argv[i], "$?") == EXIT_SUCCESS) {
            dprintf(STDOUT_FILENO, "%" PRIu32, shell->_echo);
            continue;
        }
        if (argv[i][0] == '$') {
            char *path = my_getenv(&argv[i][1], &shell->_environ);
            if (path == NULL) {
                PRINT(STDERR_FILENO, EXIT_FAILURE, ECHO_UNDEFINED_VARIABLE, &argv[i][1]);
            } else
                dprintf(STDOUT_FILENO, "%s", path);
            continue;
        }
        dprintf(STDOUT_FILENO, "%s", argv[i]);
        if (i != len - 1)
            dprintf(STDOUT_FILENO, " ");
    }
    dprintf(STDOUT_FILENO, "\n");
    return EXIT_SUCCESS;
}
