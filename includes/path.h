/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** path
*/

#ifndef PATH_H_
#define PATH_H_

#include <linux/limits.h>
#include "list.h"

char *my_getenv(const char *key, list_t **list);
char *get_absolute_path(const char *path, list_t **list);
int get_working_directory(char path[PATH_MAX]);

#endif /* !PATH_H_ */
