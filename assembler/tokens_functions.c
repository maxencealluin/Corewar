/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:58:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/24 15:59:43 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_token(t_token **token)
{
	ft_strdel((*token)->value);
	free(*token);
	*token = NULL;
}

int		*create_token(t_token **token, t_reader *reader, int start)
{
	*token = NULL;
	if (!reader->buff[start])
		return (0);
	if (!(*token = (t_token*)malloc(sizeof(t_token))))
		return (1);
	(*token)->lexem = NONE;
	(*token)->value = reader->buff + start;
	(*token)->line = line;
	(*token)->col = col;
	(*token)->next = NULL;
	return (0);
}

int		append_token(t_token *tokens, t_token *token, int state, t_reader *reader)
{
	t_token *current;
	t_lex	*list_lexem;
	int		ret;

	if (!token)
		return (0);
	if ((ret = create_value(token, reader)))
	{
		free_token(token);
		return (ret);
	}
	token->value = value;
	token->lexem = state;
	current = tokens;
	while (current->next)
		current = current->next;
	current->next = token;
	return (0);
}

t_token	*get_back_token(t_token *tokens)
{
	t_token *current;
	t_token	*last;

	current = tokens;
	while (current->next)
		current = current->next;
	if (current->next->lexem == NONE)
	{
		last = current->next;
		current->next = NULL;
		return (last);
	}
	return (NULL);
}
