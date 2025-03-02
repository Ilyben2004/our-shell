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
    i = 0;
    ops = malloc((sizeof(char **) * 20));
    while (*s)
    {
        if (*s == '>' && *(s + 1) == '>')
        {
            ops[i++] = ft_strdup(">>");
            s = s + 2;
        }
        else if (*s == '>')
        {
            ops[i++] = ft_strdup(">");
            s = s + 1;
        }
        else if (*s == '<' && *(s + 1) == '<')
        {
            ops[i++] = ft_strdup("<<");
            s = s + 2;
        }
        else if (*s == '<')
        {
            ops[i++] = ft_strdup("<");
            s = s + 1;
        }
        else if (*s == '|' && *(s + 1) == '|')
        {
            ops[i++] = ft_strdup("||");
            s = s + 2;
        }
        else if (*s == '|')
        {
            ops[i++] = ft_strdup("|");
            s = s + 1;
        }
        else if (*s == '&' && *(s + 1) == '&')
        {
            ops[i++] = ft_strdup("&&");
            s = s + 2;
        }
        else
            s++;
    }
    ops[i] = NULL;
    return (ops);
}

void put_to_tree(t_tree **node, char **commands_files, int index)
{
    printf("index = %d \n", index);

    if ((*node) != NULL)
    {
        printf("data = %s \n", (*node)->data);
        printf("left \n");
        put_to_tree(&((*node)->left), commands_files, index - 1);
        (*node)->right = malloc(sizeof(t_tree));
        (*node)->right->data = commands_files[index];
        (*node)->right->left = NULL;
        (*node)->right->right = NULL;
    }
    if ((*node) == NULL)
    {
        printf("opps index = %d \n", index);
        (*node) = malloc(sizeof(t_tree));
        (*node)->data = commands_files[index];
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }
}

static int double_char_size(char **s)
{
    int i;
    i = 0;
    while (*s)
    {
        s++;
        i++;
    }
    return (i);
}
void print_double_pointer(char **s)
{
    while (*s)
    {
        printf("%s ", *s);
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
    print_double_pointer(ops);
    print_double_pointer(commands_files);
    while (last_word >= 0)
    {
        tree->data = ops[last_word--];
        if (last_word != -1)
        {
            tree->left = malloc(sizeof(t_tree));
            tree = tree->left;
        }
    }
    tree->left = NULL;
    print_tree(head);
    put_to_tree(&head, commands_files, double_char_size(commands_files) - 1);
    return (head);
}
void print_tree(t_tree *tree)
{
    if (tree == NULL)
        return;
    print_tree(tree->left);
    printf("%s \n", tree->data);
    print_tree(tree->right);
}
