#include "parsing.h"

int ft_free(t_list *lst)
{
    t_list *helper;
    while (lst)
    {
        free(lst->content);
        helper = lst;
        lst = lst->next;
        free(helper);
    }
    return (1);
}

void *ft_malloc(size_t size , t_list **lst)
{
    t_list *new;
    new = malloc(sizeof(t_list));
    new->content = malloc(size);
    new->next = NULL;
    ft_lstadd_back(lst , new);
    return(new->content);
}