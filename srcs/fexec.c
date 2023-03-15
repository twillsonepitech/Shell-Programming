/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** sh_execve
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "errno.h"
#include "shell.h"
#include "define.h"
#include "array.h"
#include "sig_handler.h"
#include "path.h"
#include "alloc.h"

static char **create_environment(list_t **list)
{
    char **environ = (char **) init_pointer(sizeof(char *) * (length_list(list) + 1));
    size_t i = INIT;

    if (environ == NULL)
        return NULL;
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        char *line = buffer_emplace_str(3, tmp->_key, "=", tmp->_value);
        if (line == NULL)
            return NULL;
        environ[i++] = line;
    }
    environ[i] = NULL;
    return environ;
}

static const char *get_execve_failure(int errnum)
{
    for (size_t i = INIT; i < sizeof(EXECVE_FAILURE) / sizeof(EXECVE_FAILURE[0]); i++) {
        if (EXECVE_FAILURE[i]._errnum == errnum)
            return EXECVE_FAILURE[i]._response;
    }
    return "";
}

static int execute_execve(const char *path, char **argv, list_t **list)
{
    char *absolute_path = get_absolute_path(path, list);
    char **environ = create_environment(list);

    if (absolute_path == NULL)
        return EXIT_FAILURE_EPI;
    if (execve(absolute_path, (char * const *) argv, environ) == -1) {
        free(absolute_path);
        free_array(environ);
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, get_execve_failure(errno), path);
    }
    free(absolute_path);
    free_array(environ);
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

int handle_fork(char **argv, shell_t *shell)
{
    int status = 0;
    pid_t pid = fork();

    shell->_is_signal = false;
    if (pid == -1)
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, "fork(): %s.\n", strerror(errno));
    if (pid == 0) {
        if (redirections_builtin(argv, "<", "<<") == EXIT_SUCCESS && open_pipes(shell) == true && redirections_builtin(argv, ">", ">>") == EXIT_SUCCESS)
            return execute_execve(*argv, argv, &shell->_environ);
    }
    else {
        waitpid(pid, &status, 0);
        handle_signal(status, WTERMSIG(status));
        kill(pid, WTERMSIG(status));
        shell->_echo = status > 1000 ? EXIT_FAILURE : status;
        shell->_is_signal = true;
    }
    return EXIT_SUCCESS;
}
