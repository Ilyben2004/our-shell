#include "parsing.h"
#include "builtins/builtsin.h"

int ops_size(char *s, char **all_ops)
{
    int i;

    i = 0;
    while (*s)
    {
        if (extract_ops_helper(s, all_ops) >= 0)
        {
            s += ft_strlen(all_ops[extract_ops_helper(s, all_ops)]);
            i++;
        }
        else
            s++;
    }
    return (i + 1);
}

char *replace_strin_in_string(char *s, int start_string, int end_string, char *inserted_string)
{
    printf("replace start = %d , end = %d \n ", start_string, end_string);
    char *new_s;
    new_s = ft_substr(s, 0, start_string);
    new_s = ft_strjoin(new_s, inserted_string);
    new_s = ft_strjoin(new_s, s + end_string);
    return (new_s);
}

enum inside_what string_is_inside(char *s, int start)
{
    int i;
    int dbl_quotes;
    int one_quote;

    i = 0;
    dbl_quotes = 0;
    one_quote = 0;
    while (s[i] && i < start)
    {
        if (s[i] == 34)
            dbl_quotes++;
        if (s[i++] == 39)
            one_quote++;
    }
    if ((dbl_quotes % 2 == 0) && (one_quote % 2 == 0))
        return (INSIDE_NOTHING);
    else if ((dbl_quotes % 2 == 1) && (one_quote % 2 == 0))
        return (DOUBLE_QUOTES);
    else if ((dbl_quotes % 2 == 0) && (one_quote % 2 == 1))
        return (ONE_QUOTE);
    while (s[i] != 34 && s[i] != 39)
        i--;
    if (s[i] == 34)
        return (ONE_QUOTE);
    return (DOUBLE_QUOTES);
}

char *get_value(t_list *envp, char *key)
{
    t_list *value_node;
    char *content;

    if (key_is_already_exist(envp, key))
    {
        value_node = key_is_already_exist(envp, key);
        content = value_node->content;
        if (ft_strchr(content, '=') && *(ft_strchr(content, '=') + 1))
            return (ft_strdup(ft_strchr(content, '=') + 1));
        else
            return (NULL);
    }
    return (NULL);
}

// char *handle_ted(char *command)
// {
//     char * command_head = command;
//     char *ted_adresse;
//     if (ft_strchr(command, '~'))
//     {
//         ted_adresse = ft_strchr(command, '~');
//         if (inside_what (ft_strchr(command , '~')) == INSIDE_NOTHING)
//         {
//             if((ft_strchr(command , '~') == command_head ) && (my_strchr(ft_strchr(command , '~') , " \t") == (ft_strchr(command , '~') + 1)))
//             else if ()
//         }

//     }
//     return (command_head);
// }
char *parse_env(char *s, t_list *envp)
{
    char *dollr_sign;
    int i = 1;
    int j = 1;

    //s = (handle_ted(s));
    dollr_sign = ft_strchr(s, '$');
    while (dollr_sign)
    {
        i = 1;
        if (((ft_isalpha(*(dollr_sign + 1))) || (*(dollr_sign + 1) == '_')))
        {
            if (string_is_inside(s, (int)(dollr_sign - s)) == DOUBLE_QUOTES || string_is_inside(s, (int)(dollr_sign - s)) == INSIDE_NOTHING)
            {
                while (ft_isalnum(dollr_sign[i]))
                    i++;
                printf("i = %d\n", i);
                char *to_replace = get_value(envp, ft_substr(dollr_sign + 1, 0, i - 1));
                s = replace_strin_in_string(s, (int)(dollr_sign - s), (dollr_sign - s + i), to_replace);
                dollr_sign = ft_strchr(s, '$');
            }
            else
                dollr_sign = ft_strchr(dollr_sign + 1, '$');
        }
        else
            dollr_sign = ft_strchr(dollr_sign + 1, '$');
    }
    return (s);
}
