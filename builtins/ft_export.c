#include "../parsing.h"

// concatinate [ ]
// oan exesting key accept new value
//

char *remove_quotes(char *string)
{
    char *string_removed_quotes;
    char *next_quote_adresse;
    int i;

    if (!ft_strchr(string, 34) && !ft_strchr(string, 39))
        return (string);
    string_removed_quotes = ft_malloc(ft_strlen(string));
    i = 0;
    while (*string)
    {
        if ((*string == 34 || *string == 39) && ft_strchr(string + 1, *string))
        {
            next_quote_adresse = ft_strchr(string + 1, *string);
            while (++string != next_quote_adresse)
                string_removed_quotes[i++] = *string;
        }
        else if ((*string != 34 && *string != 39))
            string_removed_quotes[i++] = *string;

        string++;
    }
    string_removed_quotes[i] = '\0';
    return (string_removed_quotes);
}

static char *extract_key_from_string(char *content)
{
    char *key;
    int i;
    int j;
    i = j = 0;
    if (ft_strnstr(content, "+=", ft_strlen(content)))
        key = ft_substr(content, 0, ft_strchr(content, '=') - content);
    else if (ft_strchr(content, '='))
        key = ft_substr(content, 0, ft_strchr(content, '=') - content);
    else
        key = ft_strdup(content);
    return (key);
}

static int export_operator(char *explited_sport)
{
    if (ft_strchr(explited_sport, '=') && *(ft_strchr(explited_sport, '=') - 1) == '+')
        return (2);
    return (1);
}



t_list *key_is_already_exist(t_list *envp, char *key)
{
    while (envp)
    {
        if (!strcmp(key, extract_key_from_string((char *)envp->content)))
            return (envp);
        envp = envp->next;
    }
    return (NULL);
}

int is_valid_key(char *s)
{
    char *key;

    if (!ft_strchr(s, '=') && s[0] != '=')
        key = s;
    else if (ft_strchr(s, '='), s[0] != '=')
        key = ft_substr(s, 0, ft_strchr(s, '=') - s);
    else
        return (0);
    if (ft_isdigit(*key))
        return (0);
    while (*key)
    {
        if (ft_isalnum(*key) || *key == '_' || (*key == '+' && *(key + 1) == 0))
            key++;
        else
            return (0);
    }
    return (1);
}

static void sort_envp(t_list *export_envp)
{
    t_list *temp;
    t_list *remmember_me;
    char *helper;

    helper = NULL;
    temp = NULL;
    while (export_envp)
    {
        temp = (export_envp)->next;
        remmember_me = (export_envp)->next;
        while (temp)
        {
            if (ft_strcmp((char *)(export_envp)->content, (char *)temp->content) > 0)
            {
                helper = ((export_envp)->content);
                (export_envp)->content = temp->content;
                temp->content = helper;
            }
            export_envp = temp;
            temp = (export_envp)->next;
        }
        export_envp = remmember_me;
    }
}

static void write_expoert_envp(t_list *export_envp)
{
    char *content;
    int equal_found;

    equal_found = 0;
    while (export_envp)
    {
        content = export_envp->content;
        ft_putstr_fd("declare -x ", 1);
        while (*content)
        {
            ft_putchar_fd(*content, 1);
            if (*content == '=')
            {
                ft_putchar_fd('\x22', 1);
                equal_found = 1;
            }
            content++;
        }
        if (equal_found)
            ft_putchar_fd('\x22', 1);
        export_envp = export_envp->next;
        ft_putchar_fd('\n', 1);
    }
}
static char *get_key(char *splited_export)
{
    char *equale_adresse;
    char *add_aquale_adresse;
    char *adresse;
    equale_adresse = ft_strchr(splited_export, '=');
    add_aquale_adresse = ft_strnstr(splited_export, "+=", ft_strlen(splited_export));
    if (add_aquale_adresse && (add_aquale_adresse < equale_adresse))
        adresse = add_aquale_adresse;
    else
        adresse = equale_adresse;
    return (ft_substr(splited_export, 0, adresse - splited_export));
}
static void push_back(t_list **export_envp, char *splited_export)
{
    char *key;
    char *value;
    char *end_adresss;
    char *export_envp_content;

    key = get_key(splited_export);
    if (key_is_already_exist(*export_envp, key))
    {
        export_envp_content = key_is_already_exist(*export_envp, key)->content;
        if (export_operator(splited_export) == 1)
        {
            export_envp_content = ft_substr(export_envp_content, 0, ft_strchr(export_envp_content, '=') + 1 - export_envp_content);
            export_envp_content = ft_strjoin(export_envp_content, ft_strchr(splited_export, '=') + 1);
        }
        else if (export_operator(splited_export) == 2)
        {

            export_envp_content = ft_substr(export_envp_content, 0, ft_strlen(export_envp_content));
            export_envp_content = ft_strjoin(export_envp_content, ft_strchr(splited_export, '=') + 1);
        }
        key_is_already_exist(*export_envp, key)->content = export_envp_content;
        return;
    }
    if (!(*(ft_strchr(splited_export, '=') + 1)))
        value = ft_strdup("=");
    else
        value = ft_strdup(ft_strchr(splited_export, '='));
    ft_lstadd_back(export_envp, ft_lstnew(ft_strjoin(key, value)));
}

void ft_export(t_tree *node, t_list **export_envp)
{
    char **splited_export;
    char *key;
    char *value;

    splited_export = node->args;
    sort_envp(*export_envp);
    if (double_char_size(node->args) == 1)
        write_expoert_envp(*export_envp);
    else
    {
        splited_export++;
        *splited_export = remove_quotes(*splited_export);
        while (splited_export && *splited_export)
        {
            if (!ft_strchr(*splited_export, '=') && is_valid_key(*splited_export) && !key_is_already_exist(*export_envp, *splited_export))
                ft_lstadd_back(export_envp, ft_lstnew(*splited_export));
            else if ((ft_strnstr(*splited_export, "=", ft_strlen(*splited_export)) || ft_strnstr(*splited_export, "+=", ft_strlen(*splited_export))) && is_valid_key(*splited_export)) // 1 -> "="
                push_back(export_envp, *splited_export);
            else if (!is_valid_key(*splited_export))
                printf("export : %s : not a valid identifier\n", *splited_export);
            splited_export++;
        }
    }
}
