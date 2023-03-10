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
#define CHAR_LENGTH             (1)
#define BAD_FILE_DESCRIPTOR     (-1)

#define PRINT(__fd, __ret, __fmt, ...)              \
        do {                                        \
            dprintf(__fd, __fmt, ##__VA_ARGS__);    \
            return __ret;                           \
        } while (false);                            \

#define EXECVE_CMD_NOT_FOUND    ("%s: Command not found.\n")
#define CD_MANY_ARGUMENTS       ("cd: Too many arguments.\n")
#define ECHO_UNDEFINED_VARIABLE ("%s: Undefined variable.\n")
#define ENV_ARGUMENTS           ("env: '%s': No such file or directory\n")
#define EXIT_EXPRESSION_SYNTAX  ("exit: Expression Syntax.\n")
#define EXIT_BADLY_FORMED_NUM   ("exit: Badly formed number.\n")
#define REPEAT_FEW_ARGUMENTS    ("repeat: Too few arguments.\n")
#define REPEAT_BADLY_NUMBER     ("repeat: Badly formed number.\n")
#define SETENV_MANY_ARGUMENTS   ("setenv: Too many arguments.\n")
#define SETENV_BEGIN_LETTER     ("setenv: Variable name must begin with a letter.\n")
#define SETENV_CONTAIN_ALNUM    ("setenv: Variable name must contain alphanumeric characters.\n")
#define UNSETENV_FEW_ARGUMENTS  ("unsetenv: Too few arguments.\n")
#define WHERE_FEW_ARGUMENTS     ("where: Too few arguments.\n")
#define REDIRECT_MISSING_NAME   ("Missing name for redirect.\n")
#define REDIRECT_AMBIGUOUS_OUT  ("Ambiguous output redirect.\n")
#define REDIRECT_INVALID_CMD    ("Invalid null command.\n")

#endif /* !DEFINE_H_ */
