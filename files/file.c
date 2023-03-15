/**
 * @file file.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>

/**
 * @brief DivZero main
 * 
 * @return int 
 */
int main(void)
{
    printf("%d\n", 10 / 0);
    return 0;
}

/**
 * @brief SegFault main
 * 
 * @return int 
 */
int main(void)
{
    printf("%s\n", NULL);
    return 0;
}
