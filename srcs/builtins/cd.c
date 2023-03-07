/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** cd
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
    char new_path[PATH_MAX] = {0};

    if (chdir(path) == -1)
        PRINT(STDERR_FILENO, EXIT_FAILURE, "%s: %s.\n", path, strerror(errno));
    if (get_working_directory(new_path) == EXIT_FAILURE_EPI)
        return EXIT_FAILURE_EPI;
    inside_environment("OLDPWD", my_getenv("PWD", list), list);
    inside_environment("PWD", new_path, list);
    return EXIT_SUCCESS;
}

int cd_builtin(const char **argv, shell_t *shell)
{
    size_t len = length_array(argv);
    char *path = NULL;

    if (len >= 2)
        PRINT(STDERR_FILENO, EXIT_FAILURE, CD_MANY_ARGUMENTS);
    if (len == 0 || strcmp(argv[0], "~") == EXIT_SUCCESS)
        path = my_getenv("HOME", &shell->_list);
    else if (strcmp(argv[0], "-") == EXIT_SUCCESS)
        path = my_getenv("OLDPWD", &shell->_list);
    else
        path = (char *) argv[0];
    if (change_working_directory(path, &shell->_list) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
