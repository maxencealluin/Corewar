/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:08:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/24 16:38:34 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// ATTENTION : DIR/IND laber garde ':' au dbt

int	strncmpchr(char *s1, char *s2, int n)
{
	int	i;
	
	i = -1;
	while (++i < n && (s1[i] || s2[i]))
		if (s1[i] != s2[i])
			return (i);
	return (-1);
}

int	verif_command(t_token *token)
{
	int ret;
	int ret2;

	if ((ret = strncmpchr(token->value, "name", 4) == -1))
		token->lexem = NAME;
	else if ((ret2 = strncmpchr(token->value, "comment", 7)) != -1)
	{
		ret = ret > ret2 ? ret : ret2;
		return (print_lex_error(token->line, token->col + ret));
	}
	while (*(token->value) != '\"')
		(token->value)++;
	(token->value)++;
	return (0);
}
	
int	verif_opcode(t_token *token, int len)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (!ft_strncmp(g_instructions[i], token->value, len))
		{
			if (!(token->value = ft_itoa(i)))
				return (-1);
			return (0);
		}
	}
	return (1)
}

int	create_value(t_token *token, t_reader *reader)
{
	int		len;;

	while (*(token->value) == '\t' || *(token->value) == ' '
			|| *(token->value) == '%' || *(token->value) == '.')
	{
		(token->value)++;
		if (*(token->value) == '\t' || *(token->value) == ' ')
			(token->col)++;
	}
	if (token->lexem == REGISTER)
		(token->value)++;
	if (token->lexem == COMMENT)
		if (verif_command(token))
			return (1);
	len = reader->buffer + reader->cursor - token->value + 1;
	if (token->lexem == OPCODE)
		return (verif_opcode(token, len));
	if (token->value[len] == ':' || token->value[len] == '\"')
		len--;
	if (!(token->value = ft_strsub(token->value, len)))
		return (-1);
	return (0);
}
