/*
** EPITECH PROJECT, 2023
** Shell-Programming [WSL: Ubuntu]
** File description:
** redirections
*/

#ifndef REDIRECTIONS_H_
#define REDIRECTIONS_H_

int double_redirection_left(const char *delimiter);
int double_redirection_right(const char *filename);
int simple_redirection_left(const char *filename);
int simple_redirection_right(const char *filename);

typedef struct redirections_s {
    const char *_redirection;
    int (*_redirection_ptr) (const char *_);
} redirections_t;

static const redirections_t REDIRECTIONS[] = {
    {"<<",  &double_redirection_left},
    {">>",  &double_redirection_right},
    {"<",   &simple_redirection_left},
    {">",   &simple_redirection_right},
};

#endif /* !REDIRECTIONS_H_ */
