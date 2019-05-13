/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_instruction_decoder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:23:37 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/13 19:09:04 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_value(char *start, int size)
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
	return (value);
}

static int	write_instruction(char **instruction, int value, int type, int index)
{
	char	*tmp;
	char	*str;

	str = ft_itoa(value);
	if (index > 1)
		if (!(*instruction = ft_strappend(*instruction, ", ")))
		{
			ft_strdel(&str);
			return (-1);
		}
	tmp = *instruction;
	if (type == 1)
		*instruction = ft_strjoinarg(*instruction, "r", str);
	else if (type == 2)
		*instruction = ft_strjoinarg(*instruction, "%", str);
	else if (type == 3)
		*instruction = ft_strjoinarg(*instruction, str);
	if (!(*instruction))
	{
		ft_strdel(&str);
		return (-1);
	}
	ft_strdel(&tmp);
	return (0);
}

static int	get_arg_size(int opcode, int encoding)
{
	if (encoding == 1)
		return (1);
	if (encoding == 2)
		return(g_op_tab[opcode].dir_size);
	if (encoding == 3)
		return(2);
}

int	instruction_decoder(t_reader *reader, char *start, char **output)
{
	int		 value;
	char	encoding;
	int		size;
	int		i;
	
	encoding = 0;
	if (start[0] < 1 || start[0] > 16)
		return (1);
	if (!(*output = ft_strappend(*output, g_op_tab[start[0]].opcode)))
		return (-1);
	encoding = g_op_tab[start[0]].enc_byte ? start[1] : 128;
	reader->cursor += g_op_tab[start[0]].enc_byte ? 2 : 1;
	i = 0;
	while (encoding && ++i < 5)
	{
		encoding = g_op_tab[start[reader->cursor]].enc_byte ?\
				   start[reader->cursor + 1] : 128;
		encoding = encoding >> 8 - (i * 2);
		if (encoding < 0 || encoding > 3)
			return (1);
		if (encoding == 1)
		{
			value = get_value(start + reader->cursor, 1);
			if (value < 1 || value > 16)
				return (1);
		}
		if (encoding == 2)
			value = get_value(start + reader->cursor, g_op_tab[start[0]].dir_size);
		if (encoding == 3)
			value = get_value(start + reader->cursor, 2);
		if (write_instruction_dasm(output, value, encoding, i))
			return (-1);
		reader->cursor += get_arg_size(g_op_tab[start[0]].opcode, encoding); 
	}
	if (!(output = ft_strjoinarg(output, "\n")))
		return (-1);
	return (0);
}


