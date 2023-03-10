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
    list_t *_alias;
    list_t *_environ;
    long long _exit;
    uint32_t _echo;
} shell_t;

int handle_execve(char **argv, shell_t *shell);

int execute_shell(char const **env);
int handle_environment(char const **env, shell_t *shell);
int handle_execution_path(const char *cmd, char **argv, char **env, shell_t *shell);

bool is_required_builtins(const char *cmd);
int execute_builtins(const char *cmd, char **argv, shell_t *shell);

bool inside_environment(const char *key, const char *value, list_t **list);
char *find_command_in_alias(const char *command, list_t **alias);
void print_env(list_t **list);

int alias_builtin(char **argv, shell_t *shell);
int cd_builtin(char **argv, shell_t *shell);
int echo_builtin(char **argv, shell_t *shell);
int env_builtin(char **argv, shell_t *shell);
int exit_builtin(char **argv, shell_t *shell);
int repeat_builtin(char **argv, shell_t *shell);
int setenv_builtin(char **argv, shell_t *shell);
int unsetenv_builtin(char **argv, shell_t *shell);
int where_builtin(char **argv, shell_t *shell);

int redirections_builtin(char **argv);

typedef struct builtins_s {
    const char *_builtin;
    int (*_builtin_ptr) (char **argv, shell_t *shell);
} builtins_t;

static const builtins_t BUILTINS[] = {
    {"alias", &alias_builtin},
    {"cd", &cd_builtin},
    {"echo", &echo_builtin},
    {"env", &env_builtin},
    {"exit", &exit_builtin},
    {"repeat", &repeat_builtin},
    {"setenv", &setenv_builtin},
    {"unsetenv", &unsetenv_builtin},
    {"where", &where_builtin},
};

// deleting "env" from built-in for pipe ('|') and redirections ('<<', '>>', '<', '>')

__attribute__((unused)) static const char *builtins[] = {"alias", "cd", "echo", /*"env",*/ "exit", "repeat", "setenv", "unsetenv", "where"};

#endif /* !SHELL_H_ */
