/**
 * @file pipes.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <unistd.h>
#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "array.h"

bool open_pipes(shell_t *shell)
{
    if (shell->_pipe_count) {
        if (shell->_pipe_count == shell->_state || shell->_state != 0)
            dup2(shell->_pipes[STDOUT][STDIN], STDIN_FILENO);
        if (shell->_pipe_count != shell->_state || shell->_state == 0)
            dup2(shell->_pipes[STDIN][STDOUT], STDOUT_FILENO);
    }
    return true;
}

bool close_pipes(shell_t *shell)
{
    if (shell->_pipe_count) {
        if (shell->_pipe_count == shell->_state || shell->_state != 0)
            close(shell->_pipes[STDOUT][STDIN]);
        if (shell->_pipe_count != shell->_state || shell->_state == 0)
            close(shell->_pipes[STDIN][STDOUT]);
    }
    return true;
}

void switch_pipes(int **pipes)
{
    int *pipe;

    pipe = pipes[STDIN];
    pipes[STDIN] = pipes[STDOUT];
    pipes[STDOUT] = pipe;
}

int handle_pipes(char *command, shell_t *shell)
{
    char **pipes = str_to_word_array(command, "|");

    if (pipes == NULL)
        return EXIT_FAILURE_EPI;
    shell->_pipe_count = length_array(pipes) - 1;
    for (size_t i = INIT; i < length_array(pipes); i++) {
        shell->_state = i;
        if (handle_command(pipes[i], shell) == EXIT_FAILURE_EPI) {
            free_array(pipes);
            return EXIT_FAILURE_EPI;
        }
    }
    free_array(pipes);
    return EXIT_SUCCESS;
}
