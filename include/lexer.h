#ifndef LEXER_H
#define LEXER_H

//is this a global var ? is this authorized ? should it be a typedef ?
struct token_s
{
    struct source_s *src;       /* source of input */
    int    text_len;            /* length of token text */
    char   *text;               /* token text */
};


void free_token(struct token_s *tok);
struct token_s *tokenize(char *line);
#endif 
