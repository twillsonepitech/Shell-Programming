/**
 * @file alloc.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
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
