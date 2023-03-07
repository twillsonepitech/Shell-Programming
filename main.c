/*
** main.c for C in c:\Users\PC\Desktop\C\mysh
**
** Made by headers epitech
** Login   <thomas.willson@epitech.eu>
**
** Started on  Sat Feb 11 1:48:00 AM 2023 headers epitech
** Last update Sun Mar 4 9:43:24 PM 2023 headers epitech
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "define.h"

int main(int argc, __attribute__((unused)) char const **argv, char const **envp)
{
    if (argc != 1)
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, "Usage: [%s].\n", argv[0]);
    if (envp == NULL)
        PRINT(STDERR_FILENO, EXIT_FAILURE_EPI, "env: NULL\n");
    return execute_shell(envp);
}
