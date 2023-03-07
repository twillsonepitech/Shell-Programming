/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** list
*/

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <sys/types.h>

typedef struct list_s {
    char *_key;
    char *_value;
    struct list_s *_next;
} list_t;

bool list_add_node(list_t **list, const char *key, const char *value);
size_t length_list(list_t **list);
void free_list_by_key(list_t **list, const char *key);
void free_list(list_t **list);
void print_list(list_t **list);

#endif /* !LIST_H_ */
