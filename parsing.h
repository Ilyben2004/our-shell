#ifndef PARSING_H
#define PARSING_H

#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>

typedef enum data_type
{
    PIPE,                   // 0
    INPUT_REDIRECTION,      // 1
    APP_OUTPUT_REDIRECTION, // 2
    OUTPUT_REDIRECTION,     // 3
    APP_INPUT_REDIRECTION,  // 4
    AND,                    // 5
    OR,                     // 6
    COMMAND,                // 7
    FT_FILE,                // 8
    FT_EOF                  // 9
} e_type;

typedef struct s_tree
{
    char *path;
    char *data;
    char **args;
    char *heredoc_content;
    struct s_tree *left;
    struct s_tree *right;
    struct s_tree *parent;
    enum data_type type;
    int to_skip;
} t_tree;

// typedef struct s_tree
// {
//     char *path;
//     char *data;
//     struct s_tree *left;
//     struct s_tree *right;
//     struct s_tree *parent;
//     enum data_type type;
//     char **s;

// } t_tree;

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
t_tree *make_tree(char ***data , int * to_skip);
enum data_type get_data_type(char *s);
int commas_ops_check(char *s);
void print_double_pointer(char **s);
char **extract_files_commands_strings(char *command, char **ops);
char *my_strnstr(const char *haystack, const char *needle, size_t len);
t_tree *ilyas_parsing(char * phrase , t_list *envp);
int is_file(enum data_type type);
int is_path(char *command);
char *check_paths(char **paths, char **command);
char **extract_paths(t_list *envp);
void split_tree(t_tree *tree);
void add_paths_to_tree(t_tree *tree, char **paths);
char *my_strchr(char *s, char *target);
int ops_size(char *s, char **ops);
int extract_ops_helper(char *s, char **ops);
int ft_strcmp(char *s1, char *s2);
char *replace_strin_in_string(char *s, int start_string, int end_string, char *inserted_string);
enum inside_what string_is_inside(char *s, int start);
char *parse_env(char *s , t_list *envp);
int double_char_size(char **s);
char *skip_spaces(char *s);
char *handle_commandes_quoets(t_tree *tree);
int there_is_something_between_2_adresses(char *s1, char *s2);
char *skip_ops(char *command);
int find_next_ops(char *command);
int check_unexpected_token(char *command);
t_list *strings_to_list(char **strings);

// builts ins ////////////
void ft_echo(t_tree *node);
int ft_cd(t_tree *node , t_list * envp);
void ft_export(t_tree *node, t_list **export_envp);
char* ft_pwd(void);

/////////////////////////

#endif