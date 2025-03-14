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
    if (!strcmp(s, "<<")) // use ft_strcmp later
        return (heredoc);
    return (-1);
}

int commas_ops_check(char *s)
{
    int commas;
    if (!s)
        return (0);
    commas = 0;
    while (s && *s)
    {
        if (*s == 34)
            commas++;
        s++;
    }
    return (commas % 2 == 0);
}

char **extract_files_commands_strings(char *command, char **ops)
{
    int size = 20;
    int i;
    char **commandes_files = ft_malloc(sizeof(char **) * size);

    i = 0;
    if (!ops)
    {
        commandes_files[0] = ft_strtrim(ft_strdup(command) , " \t");
        commandes_files[1] = NULL;
        if ((commandes_files[0][0]) == 34 && ((commandes_files[0][ft_strlen(commandes_files[0]) - 1]) == 34))
            commandes_files[0] = ft_strtrim(commandes_files[0], "\x22");
        return (commandes_files);
    }
    while (*ops && size--)
    {
        if (my_strnstr(command, *ops, ft_strlen(command)))
        {
            if (!strcmp(*ops, "<"))
            {
                command = my_strnstr(command, *ops, ft_strlen(command)) + 1;
                while ((*command) && (*command == ' ') || (*command == '\t'))
                    command++;
                commandes_files[i++] = ft_substr(command, 0, my_strchr(command, " \t") - command);
                command += ft_strlen(commandes_files[i - 1]);
            }
            else
            {
                commandes_files[i] = ft_substr(command, 0, my_strnstr(command, *ops, ft_strlen(command)) - command);
                i++;
                command += (my_strnstr(command, *ops, ft_strlen(command)) - command) + ft_strlen(*ops);
            }
        }
        commandes_files[i - 1] = ft_strtrim(commandes_files[i - 1], " \t");
        if ((commandes_files[i - 1][0]) == 34 && ((commandes_files[i - 1][ft_strlen(commandes_files[i - 1]) - 1]) == 34))
            commandes_files[i - 1] = ft_strtrim(commandes_files[i - 1], "\x22");
        ops++;
    }
    commandes_files[i++] = ft_substr(command, 0, ft_strlen(command));
    commandes_files[i - 1] = ft_strtrim(commandes_files[i - 1], " \t");
    if ((commandes_files[i - 1][0]) == 34 && ((commandes_files[i - 1][ft_strlen(commandes_files[i - 1]) - 1]) == 34))
        commandes_files[i - 1] = ft_strtrim(commandes_files[i - 1], "\x22");
    commandes_files[i] = NULL;
    return (commandes_files);
}

int is_file(enum data_type type)
{
    return (type == iredirection || type == append || type == oredirection);
}