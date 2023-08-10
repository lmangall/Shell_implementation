#ifndef SHELL_H
#define SHELL_H
#include "lexer.h"    /* struct token_s */
#include "shell.h"    /* struct token_s */

#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)
struct source_s
{   
    char *buffer;       /* the input text */
    long bufsize;       /* size of the input text */
    long  curpos;       /* absolute char position in source */
};

//parser:
struct node_s *parse_simple_command(struct token_s *tok);

//shell:
int  parse_and_execute(struct source_s *src);
void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);

/**
 * @brief Returns the next character of input and updates the source pointer.
 *
 * This function returns the next character of input and updates the source pointer, so that the next call to next_char() 
 * returns the following input character. If the end of the input is reached, the function returns the special character 
 * EOF, which is defined as -1 in source.h.
 *
 * @param src A pointer to the source_s structure that contains the input string and the current position.
 * @return The next character of input or EOF if the end of the input is reached.
 *
 * @note This function modifies the source_s structure pointed to by src.
 * @warning The caller is responsible for ensuring that the source_s structure pointed to by src remains valid throughout 
 * the lifetime of the function.
 */
char next_char(struct source_s *src);
/**
 * @brief Returns (or ungets) the last character retrieved from input back to the input source.
 *
 * This function returns (or ungets) the last character retrieved from input back to the input source. 
 * The character is returned to the input source so that it can be retrieved again by the next call to next_char(). 
 * If there is no character to unget, the function does nothing.
 *
 * @param src A pointer to the source_s structure that contains the input string and the current position.
 *
 * @note This function modifies the source_s structure pointed to by src.
 * @warning The caller is responsible for ensuring that the source_s structure pointed to by src remains valid throughout 
 * the lifetime of the function.
 */
void unget_char(struct source_s *src);
/**
 * @brief Returns the next character of input without updating the source pointer.
 *
 * This function is similar to next_char() in that it returns the next character of input. The only difference is that 
 * peek_char() doesn't update the source pointer, so that the next call to next_char() returns the same input character 
 * we've just peeked at.
 *
 * @param src A pointer to the source_s structure that contains the input string and the current position.
 * @return The next character of input or EOF if the end of the input is reached.
 */
char peek_char(struct source_s *src);
/**
 * @brief Skips all whitespace characters.
 *
 * This function skips all whitespace characters in the input string. It is useful when we've finished reading a token, 
 * and we want to skip delimiter whitespaces before we read the next token.
 *
 * @param src A pointer to the source_s structure that contains the input string and the current position.
 *
 * @note This function modifies the source_s structure pointed to by src.
 * @warning The caller is responsible for ensuring that the source_s structure pointed to by src remains valid throughout 
 * the lifetime of the function.
 */
void skip_white_spaces(struct source_s *src);

#endif 