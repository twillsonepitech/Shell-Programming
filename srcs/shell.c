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

int handle_pipes(char *command, shell_t *shell)
{
    char **pipes = str_to_word_array(command, "|");

    if (pipes == NULL)
        return EXIT_FAILURE_EPI;
    shell->_pipe_count = length_array((const char **) pipes) - 1;
    for (size_t i = INIT; i < length_array((const char **) pipes); i++) {
        shell->_state = i;
        if (handle_command(pipes[i], shell) == EXIT_FAILURE_EPI) {
            free_array(pipes);
            return EXIT_FAILURE_EPI;
        }
    }
    free_array(pipes);
    return EXIT_SUCCESS;
}

int handle_shell(char *buffer, shell_t *shell)
{
    char **semicolons = str_to_word_array(buffer, ";");
    int ret = INIT;

    if (semicolons == NULL)
        return EXIT_FAILURE_EPI;
    for (size_t i = INIT; i < length_array((const char **) semicolons); i++) {
        printf("[%s]\n", semicolons[i]);
        ret = strncmp(semicolons[i], "repeat", 6) != EXIT_SUCCESS ? handle_pipes(semicolons[i], shell) : handle_command(semicolons[i], shell);
        if (ret == EXIT_FAILURE_EPI)
            break;
    }
    free_array(semicolons);
    return ret;
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
