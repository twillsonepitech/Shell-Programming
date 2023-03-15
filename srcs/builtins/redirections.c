/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** redirections
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "array.h"
#include "define.h"
#include "redirections.h"

int handle_right_redirection(const char *filename, int flag)
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

int redirections_error_handling(const char **argv)
{
    bool ok = false;

    for (size_t i = INIT; i < length_array(argv); i++) {
        if (strcmp(argv[i], "<") == EXIT_SUCCESS || strcmp(argv[i], ">") == EXIT_SUCCESS
        || strcmp(argv[i], "<<") == EXIT_SUCCESS || strcmp(argv[i], ">>") == EXIT_SUCCESS) {
            if (argv[i + 1] == NULL)
                PRINT(STDERR_FILENO, EXIT_FAILURE, REDIRECT_MISSING_NAME);
            if (i == 0)
                ok = true;
        }
    }
    if ((count_string_in_array(argv, "<") + count_string_in_array(argv, "<<")) > 1
    || (count_string_in_array(argv, ">") + count_string_in_array(argv, ">>")) > 1)
        PRINT(STDERR_FILENO, EXIT_FAILURE, REDIRECT_AMBIGUOUS_OUT);
    if (ok == true)
        PRINT(STDERR_FILENO, EXIT_FAILURE, REDIRECT_INVALID_CMD);
    return EXIT_SUCCESS;
}

static bool find_next_redirections(char ***argv, const char *redir1, const char *redir2)
{
    while (**argv) {
        if (strcmp(**argv, redir1) == EXIT_SUCCESS || strcmp(**argv, redir2) == EXIT_SUCCESS)
            return true;
        (*argv)++;
    }
    return false;
}

int redirections_builtin(char **argv, const char *redir1, const char *redir2)
{
    if (redirections_error_handling((const char **) argv) == EXIT_FAILURE)
        return EXIT_FAILURE;
    while (find_next_redirections(&argv, redir1, redir2)) {
        for (size_t i = INIT; i < sizeof(REDIRECTIONS) / sizeof(REDIRECTIONS[0]); i++) {
            if (strcmp(REDIRECTIONS[i]._redirection, *argv) == EXIT_SUCCESS)
                REDIRECTIONS[i]._redirection_ptr(*(argv + 1));
        }
        free(*argv);
        free(*(argv + 1));
        *argv = NULL;
        *(argv + 1) = NULL;
    }
    return EXIT_SUCCESS;
}
