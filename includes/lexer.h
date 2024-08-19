/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:27:44 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:59:25 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>

# define TOKEN_CMD 0
# define TOKEN_ARG_EXPAND 1
# define TOKEN_ARG_NO_EXPAND 2
# define TOKEN_PIPE 3
# define TOKEN_REDIR_TO 4
# define TOKEN_APPEND_TO 5
# define TOKEN_REDIR_FROM 6
# define TOKEN_HERE_DOCUMENT 7
# define TOKEN_AND 8

typedef struct s_token
{
	int		token_type;
	char	*string;
}	t_token;

typedef struct s_token_data
{
	char	*str;
	int		i;
	int		start;
	int		offset;
}	t_token_data;

typedef struct s_t_data
{
	int	type;
	int	i;
	int	f_and;
}	t_t_data;

// lexer.c
t_token	**lex_string(char *str);
// lexer_utils.c
int		lexer_is_special_char(char c);
int		lexer_is_quotes(char c);
int		lexer_is_exclude_chars(char c);
int		lexer_length(char *str);
char	*lexer_str_dup(char *s, int count);
// lexer_utils2.c
t_token	*get_t(char *s, int from, int to, int type);
void	bounded_by(char b, t_token_data *data);
void	all_bounded_by(t_token_data *data);
void	b_by_append(char b, t_token_data *data, t_token **tokens, int type);
void	all_bounded_by_append(t_token_data *data, t_token **tokens);
// lexer_utils3.c
void	init_tokenization_data(t_token_data *data, char *str);
void	lex_token_count_special_char(t_token_data *data, int len);
void	lex_token_count_special_char_after(t_token_data *data, int len);
int		lex_token_count(char *str);
// compress_tokens.c
t_token	**compress_tokens(t_token **tokens);
// token_free.c
void	free_token(t_token *token);
void	free_tokens(t_token **tokens);
// token_utils.c
t_token	*clone_token(t_token *token);
void	ptokens(t_token **tokens);
// libft.h
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
int		ft_strcmp(char *s1, char *s2);

#endif
