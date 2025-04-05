#include "../parsing.h"

int is_valid_key(char *s)
{
    char *key;

    if (!ft_strchr(s, '=') && s[0] != '=')
        key = s;
    else if (ft_strchr(s, '='), s[0] != '=')
        key = ft_substr(s, 0, ft_strchr(s, '=') - s);
    else
        return (0);
    if (ft_isdigit(*key))
        return (0);
    while (*key)
    {
        if (ft_isalnum(*key) || *key == '_')
            key++;
        else
            return (0);
    }
    return (1);
}

// static void push_back(char ***export_envp, char *new_var)
// {

//     size = double_char_size(*export_envp);
// }

static void sort_envp(t_list *export_envp)
{
    int i;
    int j;
    int size;
    t_list *temp;
    t_list *remmember_me;

    char *helper;

    helper = NULL;
    i = 0;
    j = 0;
    temp = NULL;
    while (export_envp)
    {
        temp = (export_envp)->next;
        remmember_me = (export_envp)->next;
        while (temp)
        {
            if (ft_strcmp((char *)(export_envp)->content, (char *)temp->content) > 0)
            {
                helper = ((export_envp)->content);
                (export_envp)->content = temp->content;
                temp->content = helper;
            }
            export_envp = temp;
            temp = (export_envp)->next;
        }
        export_envp = remmember_me;
    }
}

static void write_expoert_envp(t_list *export_envp)
{
    int keylen;
    int valuelen;
    while (export_envp)
    {
        printf("declare -x %s\n", (char *)export_envp->content);
        export_envp = export_envp->next;
    }
}
void ft_export(t_tree *node, t_list **export_envp)
{
    char **splited_export;
    char *key;
    char *value;

    splited_export = node->s;
    sort_envp(*export_envp);
    write_expoert_envp(*export_envp);
    if (double_char_size(node->s) == 1)
        write_expoert_envp(*export_envp);
    else
    {
        splited_export++;
        while (splited_export && *splited_export)
        {
            if (!ft_strchr(*splited_export, '=') && is_a_valid_key(*splited_export))
                ft_lstadd_back(export_envp, ft_lstnew(*splited_export));
            else if (ft_strchr(*splited_export, '=') && is_a_valid_key(*splited_export))
                ft_lstadd_back(export_envp, ft_substr(*splited_export, 0, ft_strchr(*splited_export, '-') - *splited_export));
            else
                printf("export : %s  : : not a valid identifier\n", *splited_export);
            splited_export++;
        }
    }
}