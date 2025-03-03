#include "parsing.h"


int main(int ac , char **av)
{
    t_list *lst;
    int i; 

    i = 0;
    lst = NULL;
    char *phrase;
    phrase = NULL;
    while (++i < ac)
    {
        phrase = ft_strjoin(phrase , av[i]);
        phrase = ft_strjoin(phrase , " ");
    }
    //printf("%s\n",phrase);
    char ** cc = extract_ops(phrase); //ft_split(phrase , "><|&");
    char ***s;
    s = malloc(sizeof(char **) * 2);
    s[0] = ft_split(phrase , "><|&");
    s[1] = cc;
    t_tree * tree = make_tree(s);
    printf("****************************************\n\n\n\n");
    print_tree(tree);
    return (ft_free(lst));
}