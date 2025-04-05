#ifndef PARSING_H
#define PARSING_H

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

enum data_type
{
    ft_pipe,      // 0
    iredirection, // 1
    append,       // 2
    oredirection, // 3
    heredoc,      // 4
        and,      // 5
    or
    ,        // 6
    command, // 7
    file,    // 8
    eof
};
typedef struct s_tree
{
    char *path;
    char *data;
    struct s_tree *left;
    struct s_tree *right;
    struct s_tree *parent;
    enum data_type type;
    char **s;

} t_tree;

enum inside_what
{
    DOUBLE_QUOTES,  // "" 0
    ONE_QUOTE,      // '' 1
    INSIDE_NOTHING, //    2
};

void *ft_malloc(size_t size);
int ft_free(t_list *lst);
char **extract_ops(char *s);
void print_tree(t_tree *tree);
t_tree *make_tree(char ***data);
enum data_type get_data_type(char *s);
int commas_ops_check(char *s);
void print_double_pointer(char **s);
char **extract_files_commands_strings(char *command, char **ops);
char *my_strnstr(const char *haystack, const char *needle, size_t len);
t_tree *ilyas_parsing(int condition);
int is_file(enum data_type type);
int is_path(char *command);
char *check_paths(char **paths, char **command);
char **extract_paths(char **envp);
void split_tree(t_tree *tree);
void add_paths_to_tree(t_tree *tree, char **paths);
char *my_strchr(char *s, char *target);
int ops_size(char *s, char **ops);
int extract_ops_helper(char *s, char **ops);
int ft_strcmp(char *s1, char *s2);
char *replace_strin_in_string(char *s, int start_string, int end_string, char *inserted_string);
enum inside_what string_is_inside(char *s, int start);
char *parse_env(char *s);
int double_char_size(char **s);
int ft_pwd(void);

// builts ins ////////////
void ft_echo(t_tree *node);
int ft_cd(t_tree *node);
void ft_export(t_tree *node, t_list **export_envp);
/////////////////////////

#endif