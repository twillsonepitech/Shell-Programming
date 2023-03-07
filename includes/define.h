/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** define
*/

#ifndef DEFINE_H_
#define DEFINE_H_

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define EXIT_FAILURE_EPI        (84)
#define INIT                    (0)
#define PROMPT                  ("> ")

#define PRINT(__fd, __ret, __fmt, ...)              \
        do {                                        \
            dprintf(__fd, __fmt, ##__VA_ARGS__);    \
            return __ret;                           \
        } while (false);                            \

#define EXECVE_CMD_NOT_FOUND    ("%s: Command not found.\n")
#define CD_MANY_ARGUMENTS       ("cd: Too many arguments.\n")
#define ENV_ARGUMENTS           ("env: '%s': No such file or directory\n")
#define EXIT_EXPRESSION_SYNTAX  ("exit: Expression Syntax.\n")
#define EXIT_BADLY_FORMED_NUM   ("exit: Badly formed number.\n")
#define SETENV_MANY_ARGUMENTS   ("setenv: Too many arguments.\n")
#define SETENV_BEGIN_LETTER     ("setenv: Variable name must begin with a letter.\n")
#define SETENV_CONTAIN_ALNUM    ("setenv: Variable name must contain alphanumeric characters.\n")
#define UNSETENV_FEW_ARGUMENTS  ("unsetenv: Too few arguments.\n")

#endif /* !DEFINE_H_ */
