#include "../parsing.h"
#include "builtsin.h"

int ft_cd(t_tree *node, t_list *envp)
{
    char *old_pwd;
    char *pwd;
    old_pwd = ft_strjoin("OLDPWD=", ft_pwd());
    if (double_char_size(node->args) > 2)
        printf("bash: cd: too many arguments\n");
    if (!node->args[1])
        return (1);
    if (chdir(node->args[1]) == -1)
        perror(node->args[1]);
    pwd = ft_strjoin("PWD=", ft_pwd());
    push_back(&envp , old_pwd);
    push_back(&envp , pwd);
    return (1);
}