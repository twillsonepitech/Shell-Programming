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
    int i = 0;

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

int handle_shell(char *buffer, shell_t *shell)
{
    char **argv = str_to_word_array(buffer, " \t\n");
    int ret = 0;

    if (argv == NULL)
        return EXIT_FAILURE_EPI;
    if (is_required_builtins(argv[0]) == true) {
        if (execute_builtins(argv[0], (const char **) &argv[1], shell) == EXIT_FAILURE_EPI) {
            shell->_echo = EXIT_FAILURE;
            return EXIT_FAILURE_EPI;
        }
        shell->_echo = EXIT_SUCCESS;
    }
    else {
        char **env = create_environment(&shell->_list);
        if (env == NULL)
            return EXIT_FAILURE_EPI;
        ret = handle_execution_path(argv[0], (const char **) argv, env, shell);
        free_array(env);
    }
    free_array(argv);
    return ret;
}

int execute_shell(char const **env)
{
    char *buffer = NULL;
    char path[PATH_MAX] = {0};
    shell_t shell = {0};
    size_t n = 0;
    ssize_t rd = 0;

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
            free_list(&shell._list);
            free(buffer);
            return EXIT_FAILURE_EPI;
        }
        if (shell._is_exit == true)
            break;
    }
    dprintf(STDOUT_FILENO, "exit\n");
    free_list(&shell._list);
    free(buffer);
    return shell._exit;
}