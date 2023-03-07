/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** alloc
*/

#include <stdlib.h>
#include <string.h>
#include "define.h"

void *init_pointer(size_t size)
{
    void *allocated_ptr = malloc(size);

    if (allocated_ptr == NULL)
        return NULL;
    (void) memset(allocated_ptr, INIT, size);
    return allocated_ptr;
}
