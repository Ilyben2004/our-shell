#include "../parsing.h"

int ft_cd(t_tree *node)
{

    if (double_char_size(node->s) > 2)
        printf("bash: cd: too many arguments\n");
    if (!node->s[1])
        return (1);
    if(chdir(node->s[1]) == -1)
        perror(node->s[1]);
    return (1);
}