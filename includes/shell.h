/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** shell
*/

#ifndef SHELL_H_
#define SHELL_H_

#include <stdbool.h>
#include <sys/types.h>
#include <stdint.h>
#include "list.h"

typedef struct shell_s {
    bool _is_exit;
    list_t *_list;
    long long _exit;
    uint32_t _echo;
} shell_t;

int execute_shell(char const **env);
int handle_environment(char const **env, shell_t *shell);
int handle_execution_path(const char *cmd, const char **argv, char **env, shell_t *shell);

bool is_required_builtins(const char *cmd);
int execute_builtins(const char *cmd, const char **argv, shell_t *shell);

void print_env(list_t **list);

int cd_builtin(const char **argv, shell_t *shell);
int echo_builtin(const char **argv, shell_t *shell);
int env_builtin(const char **argv, shell_t *shell);
int exit_builtin(const char **argv, shell_t *shell);
int setenv_builtin(const char **argv, shell_t *shell);
int unsetenv_builtin(const char **argv, shell_t *shell);

typedef struct builtins_s {
    const char *_builtin;
    int (*_builtin_ptr) (const char **argv, shell_t *shell);
} builtins_t;

static const builtins_t BUILTINS[] = {
    {"cd", &cd_builtin},
    {"setenv", &setenv_builtin},
    {"unsetenv", &unsetenv_builtin},
    {"env", &env_builtin},
    {"exit", &exit_builtin},
    {"echo", &echo_builtin},
};

#endif /* !SHELL_H_ */
