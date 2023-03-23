/**
 * @file shell.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
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

int handle_command(char *command, shell_t *shell)
{
    char **argv = str_to_word_array(command, " \t\n\r");
    char **new_argv = NULL;
    char *path = NULL;
    int ret = INIT;

    if (argv == NULL)
        return EXIT_FAILURE_EPI;
    path = find_command_in_alias(argv[0], &shell->_alias);
    new_argv = path != NULL ? str_to_word_array(path, " ") : argv;
    if (shell->_pipe_count && pipe(shell->_pipes[STDIN]) == -1)
        ret = EXIT_FAILURE_EPI;
    if (ret == EXIT_SUCCESS)
        ret = is_required_builtins(*new_argv) == true ? execute_builtins(*new_argv, new_argv + 1, shell) : handle_fork(new_argv, shell);
    close_pipes(shell);
    switch_pipes((int **) shell->_pipes);
    if (path != NULL)
        free_array(argv);
    free_array(new_argv);
    shell->_echo = !shell->_is_signal ? ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE : shell->_echo;
    return ret;
}

int manage_buffer(shell_t *shell)
{
    char path[PATH_MAX] = {INIT};
    manage_line_t line = {INIT};

    if (get_working_directory(path) == EXIT_FAILURE_EPI)
        return EXIT_FAILURE_EPI;
    if (isatty(STDIN_FILENO) != 0)
        dprintf(STDOUT_FILENO, "[%s]> ", path);
    line._rd = getline(&line._buffer, &line._n, stdin);
    if (line._rd == EOF)
        return BREAK_STATEMENT;
    line._buffer[line._rd - 1] = '\0';
    if (*line._buffer == '\0')
        return CONTINUE_STATEMENT;
    if (handle_semicolons(line._buffer, shell) == EXIT_FAILURE_EPI) {
        free(line._buffer);
        return EXIT_FAILURE_EPI;
    }
    if (shell->_is_exit == true)
        return BREAK_STATEMENT;
    return EXIT_SUCCESS;
}

int execute_shell(char **env)
{
    shell_t shell = {INIT};
    int ret = INIT;

    if (handle_environment(env, &shell) == EXIT_FAILURE_EPI)
        return EXIT_FAILURE_EPI;
    while (true) {
        ret = manage_buffer(&shell);
        if (ret == BREAK_STATEMENT)
            break;
        if (ret == CONTINUE_STATEMENT)
            continue;
        if (ret == EXIT_FAILURE_EPI) {
            free_list(&shell._environ);
            return EXIT_FAILURE_EPI;
        }
    }
    dprintf(STDOUT_FILENO, "exit\n");
    free_list(&shell._environ);
    return shell._exit;
}
