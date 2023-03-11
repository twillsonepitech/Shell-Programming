/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** alias
*/

#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "define.h"
#include "shell.h"

char *find_command_in_alias(const char *command, list_t **alias)
{
    for (list_t *tmp = *alias; tmp != NULL; tmp = tmp->_next) {
        if (strcmp(tmp->_key, command) == EXIT_SUCCESS)
            return tmp->_value;
    }
    return NULL;
}

char *get_value(size_t len, const char **argv)
{
    char *value = NULL;

    for (size_t i = INIT; i < len; i++) {
        value = (char *) realloc(value, sizeof(char) * (strlen(value == NULL ? "" : value) + strlen(argv[i]) + CHAR_LENGTH + 1));
        if (value == NULL)
            return NULL;
        i == 0 ? strcpy(value, argv[i]) : strcat(value, argv[i]);
        if (i != len - 1)
            strcat(value, " ");
    }
    return value;
}

int alias_builtin(char **argv, shell_t *shell)
{
    char *value = NULL;
    size_t len = length_array((const char **) argv);

    if (len <= 1)
        return EXIT_FAILURE;
    value = get_value(len - 1, (const char **) argv + 1);
    if (inside_environment(argv[0], value, &shell->_alias) != true) {
        if (list_add_node(&shell->_alias, argv[0], value) == false)
            return EXIT_FAILURE_EPI;
    }
    free(value);
    return EXIT_SUCCESS;
}
