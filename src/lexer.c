/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/19 14:34:00 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../include/lexer.h"
#include "../include/shell.h"

char *tok_buf = NULL;
int   tok_bufsize  = 0;
int   tok_bufindex = -1;

struct token_s eof_token = 
{
    .text_len = 0,
};

/*The add_to_buf() function adds a single character to the token buffer. 
If the buffer is full, the function takes care of extending it.*/
void add_to_buf(char c)
{
    tok_buf[tok_bufindex++] = c;

    if(tok_bufindex >= tok_bufsize)
    {
        char *tmp = realloc(tok_buf, tok_bufsize*2);

        if(!tmp)
        {
            errno = ENOMEM;
            return;
        }

        tok_buf = tmp;
        tok_bufsize *= 2;
    }
}

/*The create_token() function takes a string and converts it to a struct token_s structure. 
It takes care of allocating memory for the token's structure and text, 
and fills in the structure's member fields.
*/
struct token_s *create_token(char *str)
{
    struct token_s *tok = malloc(sizeof(struct token_s));
    
    if(!tok)
        return NULL;
	//memset: library function that set a block of memory to a specified value
	// 0 in this case.    => I think there is a libft for this
	// The question is: why do we need to set the memory to 0 ?
    memset(tok, 0, sizeof(struct token_s));
    tok->text_len = strlen(str);
    
    char *nstr = malloc(tok->text_len+1);
    
    if(!nstr)
    {
        free(tok);
        return NULL;
    }
    
    strcpy(nstr, str);
    tok->text = nstr;
    
    return tok;
}

void free_token(struct token_s *tok)
{
    if(tok->text)
		free(tok->text);
	free(tok);
}

/*
The tokenize() function is the heart and soul of our lexical scanner, 
It starts by allocating memory for our token buffer (if not already done), 
then initializes our token buffer and source pointers. 
It then calls next_char() to retrieve the next input character. 
When we reach the end of input, tokenize() returns the special eof_token, 
which marks the end of input.
*/
struct token_s *tokenize(struct source_s *src)
{

	int		endloop = 0;
	// struct token_s *eof_token = malloc(sizeof(struct token_s));
	// if(!eof_token)
	// 	return NULL;
	// eof_token->text_len = 0;

    if(!src || !src->buffer || !src->bufsize)
    {
        errno = ENODATA;//find if and how to replace errno by our ouw error handling
        //perror(ENODATA); 
        	return &eof_token;
    }
    
    if(!tok_buf)//why is this if here ?
    {
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if(!tok_buf)
        {
            errno = ENOMEM;
            return &eof_token;
        }
    }
    tok_bufindex     = 0;
    tok_buf[0]       = '\0';

    char nc = next_char(src);
    if(nc == ERRCHAR || nc == EOF)
        return &eof_token;

	//while (!(endloop) || nc != EOF)   => does not work
	while (1) 
	{
		if ((nc == ' ' || nc == '\t') && tok_bufindex > 0) 
			endloop = 1;
		else if (nc == '\n') 
			{
			if (tok_bufindex > 0) 
				unget_char(src);
			else //means that we have a newline at the beginning of the line
				add_to_buf(nc);
			endloop = 1;
			}
		else 
			add_to_buf(nc);
		if (endloop || nc == EOF)
			break;
		nc = next_char(src);
	}

    if(tok_bufindex == 0)
        return &eof_token;
    if(tok_bufindex >= tok_bufsize)
        tok_bufindex--;

    tok_buf[tok_bufindex] = '\0';
    struct token_s *tok = create_token(tok_buf);
    if(!tok)
    {
        fprintf(stderr, "error: failed to alloc buffer: %s\n",
                strerror(errno));
		return &eof_token;
    } 
    tok->src = src;
    return tok;
} 