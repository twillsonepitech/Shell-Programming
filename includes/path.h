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
const char *get_home_directory(void);

typedef enum value_info_e {
    RETURN_VALUE,
    RETURN_PATH,
    RETURN_SUBPATH,
} value_info_t;

typedef struct basic_env_variable_s {
    const char *_key;
    value_info_t _info;
    const char *_value;
} basic_env_variable_t;

static const basic_env_variable_t BASIC_VARIABLE[] = {
    {"TERM",    RETURN_VALUE,   "xterm"},
    {"PATH",    RETURN_VALUE,   "/bin:/usr/bin"},
    {"PWD",     RETURN_PATH,    ""},
    {"OLDPWD",  RETURN_PATH,    ""},
    {"HOME",    RETURN_SUBPATH, ""},
};

#endif /* !PATH_H_ */
