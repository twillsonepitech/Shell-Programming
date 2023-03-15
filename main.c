/**
 * @file main.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
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
