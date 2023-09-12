#ifndef REDIRECT_H
# define REDIRECT_H

extern long long g_exit_status;
bool	streq(char *str1, char *str2);
void redirect_input_until(struct node_s *node);
void redirect_input(struct node_s *node);
void redirect_output(struct node_s *node);
void exec_redirects(struct node_s *node);


#endif
