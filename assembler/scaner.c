/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:24:37 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/23 20:42:46 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		automate(char c, int state)
{
	int	i;

	i = -1;
	while (++i)
		if (ft_strchr(index_col[i], c))
			break ;
	return (g_automate[state][i]);
}

int		buff_manager(char buff[BUFF_SIZE + 1],  t_token *tokens, int *line, int *col)
{
	//gerer last char
	int		i;
	int		start;
	int		tmp_state;
	static int state = 0;
	t_token	*token;

	i = -1;
	start = 0;
	token = get_back_token(tokens); //check lexem NULL + si get_back set prev next a NULL
	while (buff[++i])
	{
		if (buff[i] == '\n')
		{
			(*line)++;
			*col = 1;
		}
		tmp_state = lexical_analyzer(buff[i], state);
	   	if (tmp_state == -1)
			return (print_lex_error(line, col));
		if (tmp_state && state == 0)
		{
			start = i;
			if (!(token = create_token(line, col)))
				return (-1);
		}
		state = tmp_state;
		if (g_automate[state][0] == -2)
			if (!(append_token(token, state, start, i))) //check valeur NULL || autre (join)
				return (-1);
		(*col)++;
	}
	if (!(append_token(token, state, start, i)))
		return (-1);
	return (0);
}

t_token	*scanner(int fd)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	t_token *tokens;
	int line;
	int col;

	line = 1;
	col = 1;
	state = 0;
	while (ret = read(fd, buff, BUFF_SIZE))
	{
		buff[ret] = '\0';
		if (ret == -1)
			return (NULL);
		buff_manager(buff, tokens, &line, &col);
	}
}
