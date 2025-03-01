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
    char ** cc = ft_split(phrase , "><|&");
    while (*cc)
    {
        printf("%s\n" , *cc);
        cc++;
    }
    return (ft_free(lst));
}