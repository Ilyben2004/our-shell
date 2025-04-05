#include "../parsing.h"

int ft_cd(t_tree *node)
{
    char buffer[1024];
    if (double_char_size(node->s) > 2)
        printf("bash: cd: too many arguments\n");
    if(chdir(node->s[1]) == -1)
        perror("chdir");
    printf("working dir = %s \n",getcwd(buffer , 1000));
    return (1);
}