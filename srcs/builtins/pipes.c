/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL : Ubuntu]
** File description:
** pipes
*/

#include <unistd.h>
#include "define.h"
#include "shell.h"

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
