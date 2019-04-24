/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:24:37 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/24 16:46:12 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//create value --> trimchar(espacement/%/:) + si token --> decoupage spe

int		print_lex_error(int line, int col)
{
		printf("lexical error : line %d, col %d\n", line, col);
		return (1);
}

int		automate(char c, int state)
{
	int	i;

	i = -1;
	while (++i)
		if (ft_strchr(index_col[i], c))
			break ;
	return (g_automate[state][i]);
}

int		state_manager(t_token **tokens, t_token **token, t_reader *reader, int state)
{
	char *value;

	if (state == -1)
	{
		free_token(token);
		return (print_lex_error(reader));
	}
	if (g_automate[state][0] == -2 || g_automate[state][0] == -3)
	{
		if (g_automate[state][0] == -3)
		{
			(reader->cursor)--;
			(reader->col)--;
		}
		if (!(append_token(tokens, token, state, reader)))
			return (-1);
		if ((create_token(token, reader, reader->cursor + 1)))
			return (-1);
	}
	return (0);
}

int		buff_manager(t_reader *reader,  t_token **tokens)
{
	static int	state = 0;
	t_token		*token;
	int			ret;

	if (!token = get_back_token(tokens))
		if ((create_token(&token, reader, reader->cursor)))
			return (-1);
	while (reader->buff[++(reader->cursor)])
	{
		if (reader->buff[reader->cursor] == '\n')
		{
			(reader->line)++;
			reader->col = 1;
		}
		state = automate(reader->buff[reader->cursor], state);
		if ((ret = state_manager(tokens, token, reader, state)))
			return (ret);
		(reader->col)++;
	}
	if (!(append_token(tokens, token, state, reader)))
		return (-1);
	return (0);
}

t_token	*scanner(int fd)
{
	t_reader	reader;
	int			ret;
	t_token 	*tokens;

	reader.line = 1;
	reader.col = 1;
	state = 0;
	while (ret = read(fd, reader.buff, BUFF_SIZE))
	{
		reader.buff[ret] = '\0';
		if (ret == -1)
			return (NULL);
		reader.cursor = -1;
		buff_manager(&reader, tokens, &line, &col);
	}
}
