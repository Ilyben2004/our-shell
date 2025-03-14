#include "parsing.h"

t_list *garbage_collector = NULL;

// void INThandler(int sig)
// {
//     char c;
//     signal(sig, SIG_IGN);
//     signal(SIGINT, INThandler);
//     ilyas_parsing(0);
// }

t_tree *ilyas_parsing(int condition)
{
    t_list *lst;
    int i;
    i = 0;
    lst = NULL;
    char *phrase;
    phrase = NULL;
    while (!commas_ops_check(phrase) || (ft_strncmp(phrase, "\n", ft_strlen(phrase) == 0)))
    {
        phrase = ft_strjoin(phrase, readline("$>"));
    }

    char **cc = extract_ops(phrase);
    char ***s;
    s = ft_malloc(sizeof(char **) * 2);
    s[0] = extract_files_commands_strings(phrase, cc);
    print_double_pointer(s[0]);
    s[1] = cc;
    t_tree *tree = make_tree(s);
    return (tree);
}

int main(int ac, char **av,char **envp)
{
    char **paths= extract_paths(envp);
    t_tree *tree =ilyas_parsing(1);
    split_tree(tree );
    add_paths_to_tree(tree, paths);
    print_tree(tree);
    ft_free(garbage_collector);
}