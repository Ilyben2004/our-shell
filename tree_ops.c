#include "parsing.h"

void split_tree(t_tree *tree)
{
    if (tree == NULL)
        return ;
    tree->s = ft_split(tree->data , " \t");
    split_tree(tree->right);
    split_tree(tree->left);
}
void print_tree(t_tree *tree)
{
    if (tree == NULL)
        return;
    print_tree(tree->left);
    printf("%s %d        double :", tree->data, tree->type);
    print_double_pointer(tree->s);
    if (tree->type == command)
        printf("      path : %s",tree->path);
    printf("\nnext\n");
    print_tree(tree->right);
}

void add_paths_to_tree(t_tree * tree , char **paths)
{
    if (tree == NULL)
        return ;
    if (tree->type == command)
    {
        print_double_pointer(tree->s);
        tree->path = check_paths(paths , tree->s);
    }
    add_paths_to_tree(tree->right , paths);
    add_paths_to_tree(tree->left , paths);
}