/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** shell
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "path.h"
#include "shell.h"
#include "define.h"
#include "alloc.h"
#include "array.h"

static char **create_environment(list_t **list)
{
    char **env = (char **) init_pointer(sizeof(char *) * (length_list(list) + 1));
    size_t i = INIT;

    if (env == NULL)
        return NULL;
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        char *line = buffer_emplace_str(3, tmp->_key, "=", tmp->_value);
        if (line == NULL)
            return NULL;
        env[i++] = line;
    }
    env[i] = NULL;
    return env;
}

int handle_execve(char **argv, shell_t *shell)
{
    char **environ = create_environment(&shell->_environ);
    char *path = NULL;
    int ret = INIT;

    if (environ == NULL)
        return EXIT_FAILURE_EPI;
    path = find_command_in_alias(argv[0], &shell->_alias);
    if (path != NULL) {
        char **new_argv = str_to_word_array(path, " ");
        ret = handle_execution_path(new_argv[0], new_argv, environ, shell);
        free_array(new_argv);
    } else
        ret = handle_execution_path(argv[0], argv, environ, shell);
    free_array(environ);
    return ret;
}

int handle_command(char *command, shell_t *shell)
{
    char **argv = str_to_word_array(command, " \t\n");
    int ret = INIT;

    if (argv == NULL)
        return EXIT_FAILURE_EPI;
    if (is_required_builtins(argv[0]) == true) {
        ret = execute_builtins(argv[0], &argv[1], shell);
        shell->_echo = ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    else {
        ret = handle_execve(argv, shell);
    }
    free_array(argv);
    return ret;
}

int handle_shell(char *buffer, shell_t *shell)
{
    char **argv = str_to_word_array(buffer, ";");

    if (argv == NULL)
        return EXIT_FAILURE_EPI;
    for (size_t i = INIT; i < length_array((const char **) argv); i++) {
        if (handle_command(argv[i], shell) == EXIT_FAILURE_EPI) {
            free_array(argv);
            return EXIT_FAILURE_EPI;
        }
    }
    free_array(argv);
    return EXIT_SUCCESS;
}

int execute_shell(char const **env)
{
    char *buffer = NULL;
    char path[PATH_MAX] = {INIT};
    shell_t shell = {INIT};
    size_t n = INIT;
    ssize_t rd = INIT;

    if (handle_environment(env, &shell) == EXIT_FAILURE_EPI)
        return EXIT_FAILURE_EPI;
    while (true) {
        if (get_working_directory(path) == EXIT_FAILURE_EPI)
            return EXIT_FAILURE_EPI;
        if (isatty(STDIN_FILENO) != 0)
            dprintf(STDOUT_FILENO, "[%s]> ", path);
        rd = getline(&buffer, &n, stdin);
        if (rd == EOF)
            break;
        buffer[rd - 1] = '\0';
        if (*buffer == '\0')
            continue;
        if (handle_shell(buffer, &shell) == EXIT_FAILURE_EPI) {
            free_list(&shell._environ);
            free(buffer);
            return EXIT_FAILURE_EPI;
        }
        if (shell._is_exit == true)
            break;
    }
    dprintf(STDOUT_FILENO, "exit\n");
    free_list(&shell._environ);
    free(buffer);
    return shell._exit;
}
