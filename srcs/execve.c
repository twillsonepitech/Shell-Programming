/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** sh_execve
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "define.h"
#include "array.h"
#include "sig_handler.h"
#include "path.h"

static int execute_execve(const char *path, char **argv, char **env, list_t **list)
{
    char *absolute_path = get_absolute_path(path, list);

    if (absolute_path == NULL)
        return EXIT_FAILURE_EPI;
    if (execve(absolute_path, (char * const *) argv, env) == -1) {
        free(absolute_path);
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, EXECVE_CMD_NOT_FOUND, path);
    }
    free(absolute_path);
    return EXIT_SUCCESS;
}

static void handle_signal(int status, int signal)
{
    for (size_t i = INIT; i < sizeof(SIGNAL_HANDLER) / sizeof(SIGNAL_HANDLER[0]); i++) {
        if (SIGNAL_HANDLER[i]._signal == signal) {
            printf("%s", SIGNAL_HANDLER[i]._response);
            printf("%s\n", (signal == SIGSEGV || signal == SIGFPE) && WCOREDUMP(status) ? " (core dumped)" : "");
            return ;
        }
    }
    return ;
}

int handle_execution_path(const char *path, char **argv, char **env, shell_t *shell)
{
    int ret = 0;
    int status = 0;
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork()");
        return EXIT_FAILURE_EPI;
    }
    if (pid == 0) {
        ret = redirections_builtin(argv);
        shell->_echo = ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
        if (ret != EXIT_SUCCESS)
            return ret;
        return execute_execve(path, argv, env, &shell->_environ);
    }
    else {
        waitpid(pid, &status, 0);
        handle_signal(status, WTERMSIG(status));
        shell->_echo = status > 1000 ? EXIT_FAILURE : status;
        kill(pid, WTERMSIG(status));
    }
    return EXIT_SUCCESS;
}
