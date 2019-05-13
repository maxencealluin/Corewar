/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_decoder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:58 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/13 15:37:53 by ccepre           ###   ########.fr       */
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
			ft_strde(str);
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
		ft_strdel(str);
		return (-1);
	}
	ft_strdel(tmp);
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

int	instruction_decoder(char *start, char **output, int cursor)
{
	int value;
	char	encoding;
	char *instruction;
	int	size;
	int		i;
	
	instruction = NULL;
	encoding = 0;
	if (start[0] < 1 || start[0] > 16)
		return (1);
	*instruction = ft_strappend(*instruction, g_op_tab[start[0]][0]);
	encoding = g_op_tab[start[0]][2] ? start[1] : 128;
	if (get_arg_size(start[0], encoding) > BUFF_SIZE_ASM - cursor)
		return (2); // return quoi ? save ?
	start = g_op_tab[start[0]][2] ? start + 2 : start + 1;
	i = 0;
	while (encoding && ++i < 5)
	{
		encoding = g_op_tab[start[0]][2] ? start[1] : 128;
		encoding = encoding >> 8 - (i * 2);
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

buff_manager_dasm()
{
	int i;
	int	j;

	i = -1;
	j = 0;
	str = 
	
	ft_strdel(rest
	while (reader->cursor < ret)
	{
		if (ret - reader->cursor < 14)
		{
			if (!(reader->rest = (char*)malloc(sizeof(char) *\
						(reader->nb_chars - reader->buffer + i + 1))))
				return (-1);
			reader->rest = memcpy(rest, &(buff[i]),\
				(reader->nb_chars - reader->buffer + i + 1));
			return (0);
		}
		if (instruction_decoder(&(buff[i]), output, i))
		{
			ft_strdel(rest);
					return (1);
		}
		(reader->cursor)++;
	}
		
}

int	decoder_dasm(int fd, char **output)
{
	int			inst_size;
	int			nb_chars;
	int			ret;
	t_reader	reader;

	
	reader.rest = NULL;
	reader.nb_chars = 0;
	while ((ret = read(fd, reader.buff, BUFF_SIZE_ASM)))
	{
		reader.cursor = 0;
		if (nb_chars == -1)
			return (-1);
		if ((ret = buff_manager_dasm(output, buff, nb_chars, rest)))
			return (ret);
		reader.nb_chars += ret;
	}
	if (reader.nb_chars != inst_size)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	*output;

	if (ac < 2 || verif_name(av[ac - 1], ".cor"))
		return (print_arg_error((ac < 2), av[0], ".cor"));
	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		return (print_sys_error(errno));
	if (ret = decoder(fd, &output))
	{
		ft_strdel(output);
		return (ret == -1 ? print_sys_error(errno) : 1)
	}
	ret = writer_dasm(av[1], output);
	ft_strdel(output);
	return (ret ? print_sys_error(errno) : 0);
}
