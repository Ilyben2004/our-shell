#ifndef PARSING_H
#define PARSING_H

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>

enum data_type{ft_pipe, iredirection, append, oredirection , heredoc ,and, or, command, file , filecommand};
typedef struct s_tree
{ 
    char *data; 
    struct s_tree *left; 
    struct s_tree *right;
    struct s_tree *parent;
    enum data_type type;
    char **s;

}t_tree;
void *ft_malloc(size_t size , t_list **lst);
int ft_free(t_list *lst);
char **extract_ops(char * s);
void print_tree(t_tree *tree);
t_tree * make_tree(char ***data);
enum data_type get_data_type(char *s);

#endif