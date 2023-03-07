/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** list
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

static list_t *create_node(const char *key, const char *value)
{
    list_t *node = (list_t *) malloc(sizeof(list_t));

    if (node == NULL)
        return NULL;
    node->_key = strdup(key);
    node->_value = strdup(value);
    node->_next = NULL;
    return node;
}

bool list_add_node(list_t **list, const char *key, const char *value)
{
    list_t *node = create_node(key, value);

    if (node == NULL)
        return false;
    if (*list == NULL) {
        *list = node;
    } else {
        list_t *tmp = *list;
        while (tmp->_next != NULL)
            tmp = tmp->_next;
        tmp->_next = node;
    }
    return true;
}

void print_list(list_t **list)
{
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        dprintf(STDOUT_FILENO, "[%s] & [%s]\n", tmp->_key, tmp->_value);
    }
}

size_t length_list(list_t **list)
{
    size_t cnt = 0;

    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        cnt++;
    }
    return cnt;
}

void free_list(list_t **list)
{
    list_t *tmp = NULL;

    while (*list != NULL) {
        tmp = *list;
        *list = (*list)->_next;
        free(tmp->_key);
        free(tmp->_value);
        free(tmp);
    }
}

void free_list_by_key(list_t **list, const char *key)
{
    list_t *tmp = NULL;

    if (*list == NULL)
        return;
    if (strcmp((*list)->_key, key) == EXIT_SUCCESS) {
        tmp = *list;
        *list = (*list)->_next;
        free(tmp->_key);
        free(tmp->_value);
        free(tmp);
        return;
    }
    free_list_by_key(&(*list)->_next, key);
}