#include "parsing.h"

enum data_type get_data_type(char *s)
{
    if (!strncmp(s, "||", 2))
        return (or);
    if (!strncmp(s, "&&", 2))
        return (and);
    if (!strncmp(s, ">>", 2))
        return (append);
    if (!strncmp(s, "<<", 2))
        return (heredoc);
    if (!strncmp(s, "|", 1))
        return (ft_pipe);
    if (!strncmp(s, ">", 1))
        return (oredirection);
    if (!strncmp(s, "<", 1))
        return (iredirection);

    return (-1);
}

int commas_ops_check(char *s)
{
    int commas;
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == 34 | *s == 39)
        {
            if (ft_strchr(s + 1, *s))
                s = ft_strchr(s + 1, *s) + 1;
            else
                return (0);
        }
        else
            s++;
    }
    return (1);
}

int find_next_ops(char *command)
{
    int i = 0;

    while (command[i])
    {
        if (get_data_type(&command[i]) != -1 && commas_ops_check(&command[i]))
            return (i);
        i++;
    }
    return (-1);
}
int there_is_something_between_2_adresses(char *s1, char *s2)
{
    printf("there is somthing check '%s' '%s' \n", s1, s2);
    while (s1 != s2)
    {
        if (*s1 != ' ' && *s1 != '\t')
            return (0);
        s1++;
    }
    return (1);
}
int *input_file_before_command(char *command, char **ops)
{
    int size_input_ops = 0;
    int i = 0;
    char *next_op;
    while (ops[i])
    {
        if (!ft_strcmp(ops[i], "<"))
            size_input_ops++;
        i++;
    }
    i = 0;
    int *input_ops_swap_condition = malloc(sizeof(int) * (size_input_ops + 1));
    command = skip_spaces(command);
    while (*command && i <= size_input_ops)
    {
        command = skip_spaces(command);
        if (!i && !ft_strcmp(*ops, "<"))
        {
            if (get_data_type(command) == 1 && commas_ops_check(command))
                input_ops_swap_condition[i++] = 1;
            else
                input_ops_swap_condition[i++] = 0;
            command += find_next_ops(command + 1);
            command++;
        }
        else if (find_next_ops(command) == -1)
            break;
        else if (get_data_type(command) != -1)
        {
            if (get_data_type(command) == 6 || get_data_type(command) == 5 || get_data_type(command) == 2 || get_data_type(command) == 4)
                command += 2;
            else
                command++;
            command = skip_spaces(command);
            next_op = command + find_next_ops(command);
            printf("command = %s\nnext_pos=%s\n", command, next_op);
            if (get_data_type(next_op) == iredirection)
                input_ops_swap_condition[i++] = there_is_something_between_2_adresses(command, next_op);
        }
        else if (find_next_ops(command) != -1)
            command += find_next_ops(command);
    }
    return (input_ops_swap_condition);
}

char **extract_files_commands_strings(char *command, char **ops)
{
    int size = ops_size(command, ops) + 1;
    int i;
    char **commandes_files = ft_malloc(sizeof(char **) * size);
    int next_ops_index;
    char **command_file;
    int size_input_ops = 0;
    int input_counter = 0;

    int add_to_i;
    int skip_one;
    i = 0;
    int *input_conditions = input_file_before_command(command, ops);
    while (i < 1)
    {
        printf("input_condition[%d] = %d \n", i, *(input_conditions + i));
        i++;
    }
    i = 0;
    while (ops[i])
    {
        printf("ops[%d] = '%s'\n", i, ops[i]);
        i++;
    }
    skip_one = 0;
    i = 0;
    if (!ops)
    {
        commandes_files[0] = ft_strdup(command);
        commandes_files[1] = NULL;
        return (commandes_files);
    }
    while (*command)
    {
        skip_one = 0;
        add_to_i = 0;
        command = skip_spaces(command);
        printf("command = '%s' \n current ops = '%s'\n", command, *ops);
        if (get_data_type(command) != -1 && commas_ops_check(command))
        {
            if (get_data_type(command) == 6 || get_data_type(command) == 5 || get_data_type(command) == 2 || get_data_type(command) == 4)
                command += 2;
            else
                command++;
            command = skip_spaces(command);
            printf("command = %s , *ops = %s \n", command, *ops);
            if (get_data_type(command) != -1 && commas_ops_check(command))
            {
                printf("continue \n");
                ops++;
                continue;
            }
        }

        command = skip_spaces(command);
        if ((!ft_strcmp("<", *ops)) && input_conditions[input_counter++])
        {

            commandes_files[i + 1] = ft_substr(command, 0, my_strchr(command, " \t\0") - command);
            command += ft_strlen(commandes_files[i + 1]);
            add_to_i = 1;
        }
        commandes_files[i++] = ft_substr(command, 0, find_next_ops(command));
        command += ft_strlen(commandes_files[i - 1]);
        i += add_to_i;
        ops++;
        if (find_next_ops(command) == -1 && !*skip_spaces(command))
        {
            commandes_files[i++] = ft_substr(command, 0, find_next_ops(command));
            break;
        }
    }
    commandes_files[i] = NULL;
    return (commandes_files);
}

int is_file(enum data_type type)
{
    return (type == iredirection || type == append || type == oredirection);
}