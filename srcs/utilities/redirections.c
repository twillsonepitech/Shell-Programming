/**
 * @file redirections.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "define.h"
#include "redirections.h"

static bool find_next_redirections(char ***argv, const char *redir1, const char *redir2)
{
    while (**argv) {
        if (strcmp(**argv, redir1) == EXIT_SUCCESS || strcmp(**argv, redir2) == EXIT_SUCCESS)
            return true;
        (*argv)++;
    }
    return false;
}

int redirections_builtin(char **argv, const char *redir1, const char *redir2)
{
    while (find_next_redirections(&argv, redir1, redir2)) {
        for (size_t i = INIT; i < sizeof(REDIRECTIONS) / sizeof(REDIRECTIONS[0]); i++) {
            if (strcmp(REDIRECTIONS[i]._redirection, *argv) == EXIT_SUCCESS)
                REDIRECTIONS[i]._redirection_ptr(*(argv + 1));
        }
        free(*argv);
        free(*(argv + 1));
        *argv = NULL;
        *(argv + 1) = NULL;
    }
    return EXIT_SUCCESS;
}
