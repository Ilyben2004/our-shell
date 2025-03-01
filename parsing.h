#ifndef PARSING_H
#define PARSING_H

#include "libft/libft.h"
#include <stdio.h>

typedef struct s_tree
{ 
    char *data; 
    struct s_tree *left; 
    struct s_tree *right;
    struct s_tree *parent;
    int what_is_it; // 0 -> command | 1 ->(| < > >> << && || | ...) | 2 -> infile  | 3 -> outfile 
    char **s;

}t_tree;
void *ft_malloc(size_t size , t_list **lst);
int ft_free(t_list *lst);

#endif