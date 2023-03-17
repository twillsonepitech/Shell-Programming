/**
 * @file repeat.c
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

static char *create_command_to_repeat(char **argv)
{
    char *to_repeat = NULL;
    size_t len = length_array(argv);

    for (size_t i = INIT; i < len; i++) {
        to_repeat = (char *) realloc(to_repeat, strlen(argv[i]) + 1 + strlen(to_repeat == NULL ? "" : to_repeat) + 1);
        if (to_repeat == NULL)
            return NULL;
        i == 0 ? strcpy(to_repeat, argv[i]) : strcat(to_repeat, argv[i]);
        if (i != len - 1)
            strcat(to_repeat, " ");
    }
    return to_repeat;
}

int repeat_builtin(char **argv, shell_t *shell)
{
    char *to_repeat = NULL;
    size_t len = length_array(argv);

    if (repeat_error_handling(len, argv[0]) == EXIT_FAILURE)
        return EXIT_FAILURE;
    to_repeat = create_command_to_repeat(&argv[1]);
    if (to_repeat == NULL)
        return EXIT_FAILURE_EPI;
    for (ssize_t i = INIT; i < atoll(argv[0]); i++) {
        if (handle_pipes(to_repeat, shell) == EXIT_FAILURE_EPI)
            return EXIT_FAILURE_EPI;
    }
    return EXIT_SUCCESS;
}
