/**
 * @file shell.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SHELL_H_
#define SHELL_H_

#include <stdbool.h>
#include <sys/types.h>
#include <stdint.h>
#include <errno.h>
#include "list.h"

typedef struct shell_s {
    bool _is_child;
    bool _is_exit;
    bool _is_signal;
    int32_t _pipes[2][2];
    list_t *_alias;
    list_t *_environ;
    long long _exit;
    uint32_t _echo;
    uint32_t _pipe_count;
    uint32_t _state;
} shell_t;

typedef struct manage_line_s {
    char *_buffer;
    size_t _n;
    ssize_t _rd;
} manage_line_t;

int handle_semicolons(char *buffer, shell_t *shell);
int handle_pipes(char *command, shell_t *shell);
int handle_command(char *command, shell_t *shell);

int execute_shell(char **env);
int handle_environment(char **env, shell_t *shell);
int handle_fork(char **argv, shell_t *shell);

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

int redirections_builtin(char **argv, const char *redir1, const char *redir2);
int manage_redirection_file_creation(char *command);

bool open_pipes(shell_t *shell);
bool close_pipes(shell_t *shell);
void switch_pipes(int **pipes);

typedef struct builtins_s {
    const char *_builtin;
    int (*_builtin_ptr) (char **argv, shell_t *shell);
} builtins_t;

static const builtins_t BUILTINS[] = {
    {"alias",    &alias_builtin},
    {"cd",       &cd_builtin},
    {"echo",     &echo_builtin},
    {"env",      &env_builtin},
    {"exit",     &exit_builtin},
    {"repeat",   &repeat_builtin},
    {"setenv",   &setenv_builtin},
    {"unsetenv", &unsetenv_builtin},
    {"where",    &where_builtin},
};

// deleting "env" from built-in for pipe ('|') and redirections ('<<', '>>', '<', '>')
__attribute__((unused)) static const char *builtins[] = {
    "alias",
    "cd",
    "echo",
    "env", // TO DELETE ?
    "exit",
    "repeat",
    "setenv",
    "unsetenv",
    "where"
};

typedef struct execve_failure_s {
    int _errnum;
    const char *_response;
} execve_failure_t;

static const execve_failure_t EXECVE_FAILURE[] = {
    {ENOENT,  "%s: Command not found.\n"},
    {ENOEXEC, "%s: Exec format error. Wrong Architecture.\n"},
    {EACCES,  "%s: Permission denied.\n"},
};

#endif /* !SHELL_H_ */
