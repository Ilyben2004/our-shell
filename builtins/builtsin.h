#ifndef BUILTSIN_H
# include "../parsing.h"

// builts_ins_helper_funcs
char *remove_quotes(char *string);
char *extract_key_from_string(char *content);
int export_operator(char *explited_sport);
t_list *key_is_already_exist(t_list *envp, char *key);
int is_valid_key(char *s);
void push_back(t_list **export_envp, char *splited_export);
char *get_key(char *splited_export);

#endif