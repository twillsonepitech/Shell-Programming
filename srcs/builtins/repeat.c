/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL : Ubuntu]
** File description:
** repeat
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include "array.h"
#include "define.h"
#include "shell.h"
#include "path.h"

static int repeat_error_handling(size_t len, const char *str)
{
    if (len <= 1)
        PRINT(STDERR_FILENO, EXIT_FAILURE, REPEAT_FEW_ARGUMENTS);
    for (size_t i = INIT; i < strlen(str); i++) {
        if (isdigit(str[i]) == false)
            PRINT(STDERR_FILENO, EXIT_FAILURE, REPEAT_BADLY_NUMBER);
    }
    return EXIT_SUCCESS;
}

static int execute_repeated_command(char **argv, shell_t *shell)
{
    char **new_argv = NULL;
    char *path = find_command_in_alias(argv[0], &shell->_alias);
    int ret = INIT;

    new_argv = path != NULL ? str_to_word_array(path, " ") : argv;
    if (is_required_builtins(new_argv[0]) == true) {
        ret = execute_builtins(new_argv[0], &new_argv[1], shell);
        shell->_echo = ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    else {
        ret = handle_execve(new_argv, shell);
    }
    if (path != NULL)
        free_array(new_argv);
    return ret;
}

int repeat_builtin(char **argv, shell_t *shell)
{
    size_t len = length_array((const char **) argv);

    if (repeat_error_handling(len, argv[0]) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (ssize_t i = INIT; i < atoll(argv[0]); i++) {
        if (execute_repeated_command(&argv[1], shell) == EXIT_FAILURE_EPI)
            return EXIT_FAILURE_EPI;
    }
    return EXIT_SUCCESS;
}
