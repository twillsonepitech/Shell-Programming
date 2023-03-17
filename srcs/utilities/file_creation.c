/**
 * @file file_creation.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "define.h"

static bool str_is_left_redirections(const char *str)
{
    return strcmp(str, "<") == EXIT_SUCCESS || strcmp(str, "<<") == EXIT_SUCCESS;
}

static bool str_is_right_redirections(const char *str)
{
    return strcmp(str, ">") == EXIT_SUCCESS || strcmp(str, ">>") == EXIT_SUCCESS;
}

static bool str_is_redirections(const char *str)
{
    return str_is_left_redirections(str) || str_is_right_redirections(str);
}

static int redirections_error_handling(char **argv)
{
    bool ok = false;

    for (size_t i = INIT; i < length_array(argv); i++) {
        if (str_is_redirections(argv[i]) == true) {
            if (argv[i + 1] == NULL)
                PRINT(STDERR_FILENO, EXIT_FAILURE, REDIRECT_MISSING_NAME);
            if (i == 0)
                ok = true;
        }
    }
    if ((count_string_in_array(argv, "<") + count_string_in_array(argv, "<<")) > 1
    || (count_string_in_array(argv, ">") + count_string_in_array(argv, ">>")) > 1)
        PRINT(STDERR_FILENO, EXIT_FAILURE, REDIRECT_AMBIGUOUS_OUT);
    if (ok == true)
        PRINT(STDERR_FILENO, EXIT_FAILURE, REDIRECT_INVALID_CMD);
    return EXIT_SUCCESS;
}

int manage_redirection_file_creation(char *command)
{
    char **argv = str_to_word_array(command, " \t\n\r");

    if (argv == NULL)
        return EXIT_FAILURE_EPI;
    if (redirections_error_handling(argv) == EXIT_FAILURE) {
        free_array(argv);
        return EXIT_FAILURE;
    }
    for (size_t i = INIT; i < length_array(argv); i++) {
        if (str_is_right_redirections(argv[i]) == true) {
            if (creat(argv[i + 1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == BAD_FILE_DESCRIPTOR)
                return EXIT_FAILURE_EPI;
        }
    }
    free_array(argv);
    return EXIT_SUCCESS;
}
