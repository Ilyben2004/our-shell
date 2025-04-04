#include "../parsing.h"

static char *skip_spaces(char *s)
{
    while (*s && (*s == ' ' || *s == '\t'))
        s++;
    return (s);
}



static void ft_echo_write(char *to_write, int n_option)
{
    while (*to_write)
    {
        if (*to_write == 34 || *to_write == 39)
        {
            printf("%s", ft_substr(to_write + 1, 0, ft_strchr(to_write + 1, *to_write) - (to_write + 1)));
            to_write = ft_strchr(to_write + 1, *to_write) + 1;
        }
        else if (*to_write == ' ' || *to_write == '\t')
        {
            printf(" ");
            to_write = skip_spaces(to_write);
        }
        else
        {
            while (*to_write && (*to_write != ' ' && *to_write != '\t' && *to_write != 34 && *to_write != 39))
            {
                printf("%c", *to_write);
                to_write++;
            }
        }
    }
}

void ft_echo(char *command)
{
    int n_option;
    char **check_n_option;
    char *to_write;

    to_write = NULL;
    if (ft_strnstr(command, "-n", ft_strlen(command)))
    {
        check_n_option = ft_split(command, " \t");
        if (ft_strcmp(check_n_option[1], "-n") == 0)
            n_option = 1;
        else
            n_option = 0;
    }
    else
        n_option = 0;
    if (n_option)
        to_write = ft_strnstr(command, "-n", ft_strlen(command)) + 2;
    else
        to_write = command + 4;

    ft_echo_write(to_write, n_option);
}
