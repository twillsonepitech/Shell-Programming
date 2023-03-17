/**
 * @file semicolons.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "array.h"
#include "define.h"

int handle_semicolons(char *buffer, shell_t *shell)
{
    char **semicolons = str_to_word_array(buffer, ";");
    int ret = INIT;

    if (semicolons == NULL)
        return EXIT_FAILURE_EPI;
    for (size_t i = INIT; i < length_array(semicolons); i++) {
        ret = manage_redirection_file_creation(semicolons[i]);
        if (ret != EXIT_SUCCESS)
            break;
        ret = strncmp(semicolons[i], "repeat", 6) != EXIT_SUCCESS ? handle_pipes(semicolons[i], shell) : handle_command(semicolons[i], shell);
        if (ret == EXIT_FAILURE_EPI)
            break;
    }
    free_array(semicolons);
    return ret;
}
