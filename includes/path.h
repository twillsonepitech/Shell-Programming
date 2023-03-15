/**
 * @file path.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PATH_H_
#define PATH_H_

#include <linux/limits.h>
#include "list.h"

char *my_getenv(const char *key, list_t **list);
char *get_absolute_path(const char *path, list_t **list);
int get_working_directory(char path[PATH_MAX]);

#endif /* !PATH_H_ */
