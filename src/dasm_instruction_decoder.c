/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_instruction_decoder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:23:37 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/13 17:51:45 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_value(char **start, int size)
{
	int value;
	int tmp;
	int i;

	value = 0;
	i = -1;
	while (++i < size)
	{
		tmp = *start + i;
		tmp = tmp << 8 * (size - i - 1);
		value = value | tmp;
	}
	(*start) += size;
	return (value);
}

int	write_instruction(char **instruction, int value, int type, int index)
{
	char	*tmp;
	char	*str;

	str = ft_itoa(value);
	if (i > 1)
		if (!(*instruction = ft_strappend(*instruction, ", ")))
		{
			ft_strdel(&str);
			return (-1);
		}
	tmp = *instruction;
	if (type == 1)
		*instruction = ft_joinarg(*instruction, "r", str);
	else if (type == 2)
		*instruction = ft_joinarg(*instruction, "%", str);
	else if (type == 3)
		*instruction = ft_joinarg(*instruction, str);
	if (!(*instruction))
	{
		ft_strdel(&str);
		return (-1);
	}
	ft_strdel(&tmp);
	return (0);
}

int	get_arg_size(int opcode, int encoding)
{
	int size;

	size = 0;
	i = 0;
	while (encoding && ++i < 5)
	{
		encoding = encoding >> 8 - (i * 2);
		if (encoding == 1)
			size += 1;
		if (encoding == 2)
			size += g_op_tab[opcode][3];
		if (encoding == 3)
			size += 2;
	}
	return (size);
}

int	instruction_decoder(t_reader *reader, char *start, char **output)
{
	int		 value;
	char	encoding;
	char 	*instruction;
	int		size;
	int		i;
	
	instruction = NULL;
	encoding = 0;
	if (start[0] < 1 || start[0] > 16)
		return (1);
	if (!(*instruction = ft_strappend(*instruction, g_op_tab[start[0]][0])))
		return (-1);
	encoding = g_op_tab[start[0]][2] ? start[1] : 128;
	start = g_op_tab[start[0]][2] ? start + 2 : start + 1;
	reader->cursor += g_op_tab[start[0]][2] ? 2 : 1;
	i = 0;
	while (encoding && ++i < 5)
	{
		encoding = g_op_tab[start[0]][2] ? start[1] : 128;
		encoding = encoding >> 8 - (i * 2);
		reader->cursor += get_arg_size(g_op_tab[start[0]][1], encoding); 
		if (encoding < 0 || encoding > 3)
			return (1);
		if (encoding == 1)
		{
			value = get_value(start, 1);
			if (value < 1 || value > 16)
				return (1);
		}
		if (encoding == 2)
			value = get_value(start, g_op_tab[start[0]][3]);
		if (encoding == 3)
			value = get_value(start, 2);
		if (write_instruction_dasm(&instruction, value, encoding, i))
			return (-1);
	}
	if (!(output = ft_joinarg(output, instruction, "\n")))
		return (-1);
	return (0);
}


