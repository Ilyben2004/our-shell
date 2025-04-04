#include "../parsing.h"

static char *skip_spaces(char *s)
{
    while (*s && (*s == ' ' || *s == '\t'))
        s++;
    return (s);
}



static void ft_echo_write(char *to_write, int n_option)
{
    int fd;
    int i_did_write;

    fd = 1;
    while (to_write && *to_write)
    {
        if (*to_write == 34 || *to_write == 39)
        {
            i_did_write = 1;
            ft_putstr_fd( ft_substr(to_write + 1, 0, ft_strchr(to_write + 1, *to_write) - (to_write + 1)) , fd);
            to_write = ft_strchr(to_write + 1, *to_write) + 1;
        }
        else if (*to_write == ' ' || *to_write == '\t')
        {
            to_write = skip_spaces(to_write);
            if(*to_write && i_did_write)
                ft_putchar_fd(' ' , fd);
        }
        else
        {
            while (*to_write && (*to_write != ' ' && *to_write != '\t' && *to_write != 34 && *to_write != 39))
            {
                ft_putchar_fd(*to_write , fd);
                to_write++;
            }
            i_did_write = 1;
        }
    }
    if(!n_option)
        ft_putchar_fd('\n' , 1);
}

void ft_echo(t_tree *node)
{
    int n_option;
    char **check_n_option;
    char *to_write;
    int n_found_inside_quotes;

    n_found_inside_quotes  = 0;
    to_write = NULL;
    if (ft_strnstr(node->data, "-n", ft_strlen(node->data)))
    {
        check_n_option = node->s;
        if (ft_strcmp(check_n_option[1], "-n") == 0 )
            n_option = 1;
        else if (ft_strcmp(check_n_option[1], "'-n'") == 0 || ft_strcmp(check_n_option[1], "\x22-n\x22") == 0)
            n_option = ++n_found_inside_quotes;
        else
            n_option = 0;
    }
    else
        n_option = 0;
    if (n_option)
        to_write = ft_strnstr(node->data, "-n", ft_strlen(node->data)) + 2 + n_found_inside_quotes;
    else
        to_write = node->data + 4;
    ft_echo_write(to_write, n_option);
}
