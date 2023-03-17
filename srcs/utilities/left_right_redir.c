/**
 * @file left_right_redir.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "define.h"

static int handle_right_redirection(const char *filename, int flag)
{
    int out_fd = open(filename, O_WRONLY | O_CREAT | flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (out_fd == BAD_FILE_DESCRIPTOR)
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, "%s: %s.\n", filename, strerror(errno));
    dup2(out_fd, STDOUT_FILENO);
    close(out_fd);
    return EXIT_SUCCESS;
}

int double_redirection_left(const char *delimiter)
{
    char *buffer = NULL;
    int pipes[2];
    size_t n;
    ssize_t rd;

    if (pipe(pipes) == BAD_FILE_DESCRIPTOR)
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, "pipe(): %s.\n", strerror(errno));
    while (true) {
        dprintf(STDOUT_FILENO, "? ");
        rd = getline(&buffer, &n, stdin);
        if (rd == EOF)
            break;
        buffer[rd - 1] = '\0';
        if (strcmp(buffer, delimiter) == EXIT_SUCCESS)
            break;
        write(pipes[STDOUT], buffer, strlen(buffer));
        write(pipes[STDOUT], "\n", strlen("\n"));
    }
    free(buffer);
    close(pipes[STDOUT]);
    dup2(pipes[STDIN], STDIN_FILENO);
    close(pipes[STDIN]);
    return EXIT_SUCCESS;
}

int double_redirection_right(const char *filename)
{
    return handle_right_redirection(filename, O_APPEND);
}

int simple_redirection_left(const char *filename)
{
    int in_fd = open(filename, O_RDONLY);

    if (in_fd == BAD_FILE_DESCRIPTOR)
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, "%s: %s\n", filename, strerror(errno));
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
    return EXIT_SUCCESS;
}

int simple_redirection_right(const char *filename)
{
    return handle_right_redirection(filename, O_TRUNC);
}
