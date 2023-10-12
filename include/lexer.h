#ifndef LEXER_H
#define LEXER_H

char **lexer(char *line);

void	replaceform_feed_with_spaces(char *str);
char	*check_quotes_replace_ff(char *line);
// void	print_double_pointer_to_char(char **strArray);
int		contains_two(char *str, char c);
char	**put_space_back(char **tokens);

#endif 
