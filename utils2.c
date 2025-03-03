#include "parsing.h"

enum data_type get_data_type(char *s)
{
    if (!strcmp(s, "|")) // use ft_strcmp later
        return (ft_pipe);
    if (!strcmp(s, "||")) // use ft_strcmp later
        return (or);
    if (!strcmp(s, "&&")) // use ft_strcmp later
        return (and);
    if (!strcmp(s, ">")) // use ft_strcmp later
        return (oredirection);
    if (!strcmp(s, ">>")) // use ft_strcmp later
        return (append);
    if (!strcmp(s, "<")) // use ft_strcmp later
        return (oredirection);
    return (-1);
}