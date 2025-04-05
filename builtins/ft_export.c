#include "../parsing.h"

static void sa(t_list **a)
{
    int size;
    t_list *helper;
    t_list *helper2;

    size = ft_lstsize(*a);
    if (size >= 2)
    {
        if (size == 2)
        {
            (*a)->next->next = *a;
            helper = (*a)->next;
            (*a)->next = NULL;
            *a = helper;
        }
        else
        {
            helper = (*a)->next->next;
            helper2 = (*a)->next;
            (*a)->next->next = *a;
            (*a)->next = helper;
            *a = helper2;
        }
    }
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
    printf("im here \n");
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
    // else
    // {
    //     splited_export++;
    //     while (splited_export && *splited_export)
    //     {
    //         if (!ft_strchr(*splited_export, '=') && is_a_valid_key(*splited_export))
    //             push_back(&export_envp, *splited_export);
    //         else if (ft_strchr(*splited_export, '=') && is_a_valid_key(*splited_export))
    //             push_back(&export_envp, ft_substr(*splited_export, 0, ft_strchr(*splited_export, '-') - *splited_export));
    //         else
    //             printf("export : %s  : : not a valid identifier\n", *splited_export);
    //         splited_export++;
    //     }
    // }
}