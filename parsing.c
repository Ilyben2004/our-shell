#include "parsing.h"

void sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler);
    printf("you called me ?\n");
    ilyas_parsing(0);
}

t_tree *ilyas_parsing(int condition)
{
    t_list *lst;
    int i;
    i = 0;
    lst = NULL;
    char *phrase;
    phrase = NULL;
    signal(SIGINT, sigintHandler);
    while (!commas_ops_check(phrase) || (ft_strncmp(phrase , "\n" ,ft_strlen(phrase) == 0)))
    {
        phrase = ft_strjoin(phrase, readline("$>"));
    }

    char **cc = extract_ops(phrase); // ft_split(phrase , "><|&");
    char ***s;
    s = malloc(sizeof(char **) * 2);
    s[0] = extract_files_commands_strings(phrase, cc);
    // print_double_pointer(s[0]);
    s[1] = cc;
    t_tree *tree = make_tree(s);
    return (tree);
}

int main(int ac, char **av)
{
    signal(SIGINT, sigintHandler);
    ilyas_parsing(1);
}