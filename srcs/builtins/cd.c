/**
 * @file cd.c
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
#include <errno.h>
#include "array.h"
#include "define.h"
#include "path.h"
#include "shell.h"

static int change_working_directory(const char *path, list_t **list)
{
    char new_path[PATH_MAX] = {INIT};

    if (chdir(path) == -1)
        PRINT(STDERR_FILENO, EXIT_FAILURE, "%s: %s.\n", path, strerror(errno));
    if (get_working_directory(new_path) == EXIT_FAILURE_EPI)
        return EXIT_FAILURE_EPI;
    inside_environment("OLDPWD", my_getenv("PWD", list), list);
    inside_environment("PWD", new_path, list);
    return EXIT_SUCCESS;
}

int cd_builtin(char **argv, shell_t *shell)
{
    size_t len = length_array((const char **) argv);
    char *path = NULL;

    if (len >= 2)
        PRINT(STDERR_FILENO, EXIT_FAILURE, CD_MANY_ARGUMENTS);
    if (len == 0 || strcmp(argv[0], "~") == EXIT_SUCCESS)
        path = my_getenv("HOME", &shell->_environ);
    else if (strcmp(argv[0], "-") == EXIT_SUCCESS)
        path = my_getenv("OLDPWD", &shell->_environ);
    else
        path = argv[0];
    if (change_working_directory(path, &shell->_environ) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
