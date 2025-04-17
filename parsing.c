#include "parsing.h"

t_list *garbage_collector = NULL;

// void INThandler(int sig)
// {
//     char c;
//     signal(sig, SIG_IGN);
//     signal(SIGINT, INThandler);
//     ilyas_parsing(0);
// }

int there_is_one_word(char *command)
{
    if (*command == 34 || *command == 39)
        command = ft_strchr(command + 1, *command);
    else
    {
        while (*command && (*command != ' ' && *command != '\t'))
            command++;
    }
    printf("command = %s \n", command);
    command = skip_spaces(command);
    if (get_data_type(command) != -1 || *command == 0)
        return (1);
    return (0);
}
int *get_to_skip(char *command, char **ops)
{
    int i;

    i = 0;
    int *to_skip = ft_malloc(sizeof(int) * double_char_size(ops));
    if (!ops || !*ops)
        return (NULL);
    while (1)
    {
        command += find_next_ops(command);
        if (find_next_ops(skip_ops(command)) == -1)
        {
            to_skip[i++] = 0;
            break;
        }
        else if (there_is_something_between_2_adresses(skip_ops(command), skip_ops(command) + find_next_ops(skip_ops(command))) && there_is_one_word(skip_ops(skip_ops(command) + find_next_ops(skip_ops(command)))))
            to_skip[i++] = 1;
        else
            to_skip[i++] = 0;
        command = skip_ops(command);
    }
    return (to_skip);
}

t_tree *ilyas_parsing(t_list *envp)
{
//// spliiit with new_line <3
    char **paths = extract_paths(envp);
    int *to_skip;
    t_list *lst;
    int i;
    i = 0;
    lst = NULL;
    char *phrase;
    phrase = readline("$>");

    add_history(phrase);
    phrase = parse_env(phrase, envp);
    if (*skip_spaces(phrase) == 0)
        return (ilyas_parsing(envp));
    if (!check_unexpected_token(phrase))
        return (printf("unexpexted token \n"), NULL);
    char **cc = extract_ops(phrase);
    char ***s;
    s = ft_malloc(sizeof(char **) * 2);
    s[0] = extract_files_commands_strings(phrase, cc);
    s[1] = cc;
    to_skip = get_to_skip(phrase, cc);
    // while (*cc)
    // {
    //     printf("%s = %d \n", *cc, *to_skip);
    //     cc++;
    //     to_skip++;
    // }
    // exit(0);
    t_tree *tree = make_tree(s, to_skip);
    split_tree(tree);
    add_paths_to_tree(tree, paths);
    print_tree(tree);
    return (tree);
}

int main(int ac, char **av, char **envp)
{

    int i = 0;
    t_tree *tree;
    t_list *envp_list = strings_to_list(envp);
    while ((tree = ilyas_parsing(envp_list)))
    {
        i++;
    }
    return (0);
}

// // built ins tests

// int main(int ac, char **av)
// {
//     t_tree node;
//     while (1)
//     {
//         node.data = readline("$>");
//         if (!commas_ops_check(node.data))
//             return (printf("syntax error near unexpected token \n"), 1);
//         node.s = ft_split(node.data, " \t");
//         ft_echo(&node);
//     }
// }

// int main(int ac , char **av)
// {
//     t_tree node;
//     node.data =  readline("$>");
//     node.s = ft_split(node.data , " \t");
//     ft_cd(&node);

// }

// int main(int ac , char **av)
// {
//     ft_pwd();
// }

// EXPORT

// int main(int ac, char **av, char **envp)
// {
//     t_tree node;
//     t_list *env;
//     env = strings_to_list(envp);
//     node.data = readline("$>");
//     node.args = ft_split(node.data, " \t");
//     ft_cd(&node, env);
//     node.data = readline("$>");
//     node.args = ft_split(node.data, " \t");
//     ft_export(&node, &env);
// }