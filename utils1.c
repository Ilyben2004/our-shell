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

void *ft_malloc(size_t size, t_list **lst)
{
    t_list *new;
    new = malloc(sizeof(t_list));
    new->content = malloc(size);
    new->next = NULL;
    ft_lstadd_back(lst, new);
    return (new->content);
}
char **extract_ops(char *s)
{
    char **ops;
    int i;
    int op_found;

    op_found = 0;
    i = 0;
    ops = malloc((sizeof(char **) * 20));
    while (*s)
    {
        if (*s == '>' && *(s + 1) == '>' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup(">>");
            s = s + 2;
            op_found = 1;
        }
        else if (*s == '>' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup(">" );
            s = s + 1;
            op_found = 1;
        }
        else if (*s == '<' && *(s + 1) == '<' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup("<<");
            s = s + 2;
            op_found = 1;
        }
        else if (*s == '<' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup("<");
            s = s + 1;
            op_found = 1;
        }
        else if (*s == '|' && *(s + 1) == '|' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup("||");
            s = s + 2;
            op_found = 1;
        }
        else if (*s == '|' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup("|");
            s = s + 1;
            op_found = 1;
        }
        else if (*s == '&' && *(s + 1) == '&' && commas_ops_check(s))
        {
            ops[i++] = ft_strdup("&&");
            s = s + 2;
            op_found = 1;
        }
        else
            s++;
    }
    ops[i] = NULL;
    if (!op_found)
        ops = NULL;
    return (ops);
}

void put_to_tree(t_tree **node, char **commands_files, int index , int one_node)
{

    if (one_node)
    {
        (*node)->right = NULL;
        (*node)->data = commands_files[index];
        (*node)->type = filecommand;
        return;
    }
    if ((*node) != NULL)
    {
        put_to_tree(&((*node)->left), commands_files, index - 1 , one_node);
        (*node)->right = malloc(sizeof(t_tree));
        (*node)->right->data = commands_files[index];
        (*node)->right->type = filecommand;
        (*node)->right->left = NULL;
        (*node)->right->right = NULL;
    }
    if ((*node) == NULL)
    {
        (*node) = malloc(sizeof(t_tree));
        (*node)->data = commands_files[index];
        (*node)->type = filecommand;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }
}

static int double_char_size(char **s)
{
    int i;
    i = 0;
    while (s && *s)
    {
        s++;
        i++;
    }
    return (i);
}
void print_double_pointer(char **s)
{
    if (s == NULL)
        printf("double pointer is NULL\n");
    while (s && *s)
    {
        printf("%s,", *s);
        s++;
    }
    printf("\n");
}

t_tree *make_tree(char ***data)
{
    char **commands_files;
    char **ops;
    t_tree *tree;
    t_tree *head;
    int last_word;

    last_word = double_char_size(data[1]) - 1;
    tree = malloc(sizeof(t_tree));
    head = tree;
    commands_files = data[0];
    ops = data[1];
    while (last_word >= 0)
    {
        tree->data = ops[last_word--];
        tree->type = get_data_type(tree->data);
        if (last_word != -1)
        {
            tree->left = malloc(sizeof(t_tree));
            tree = tree->left;
        }
    }
    tree->left = NULL;
    put_to_tree(&head, commands_files, double_char_size(commands_files) - 1 ,(double_char_size(commands_files) - 1 == 0) && (ops == NULL));
    return (head);
}
void print_tree(t_tree *tree)
{
    if (tree == NULL)
        return;
    print_tree(tree->left);
    printf("%s %d\n", tree->data , tree->type);
    print_tree(tree->right);
}
