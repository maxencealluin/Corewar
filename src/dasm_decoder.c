/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_decoder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:58 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/13 18:56:59 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	buff_manager_dasm (t_reader *reader, char **output, int ret)
{
	char	*start;

	if (!(start = (char*)ft_memalloc(reader->col + ret)))
	{
		ft_strdel(&(reader->rest));
		return (-1);
	}	
	start = (char*)ft_memcpy(start, reader->rest, reader->col);
   	ft_memcpy(start + reader->col, reader->buff, ret);	
	ft_strdel(&(reader->rest));
	ret += reader->col;
	while (reader->cursor < ret)
	{
		if (ret - reader->cursor < 14)
		{
			if (!(reader->rest = (char*)malloc(sizeof(char) *\
						(ret - reader->cursor + 1))))
			{
				ft_strdel(&start);
				return (-1);
			}
			reader->col = ret - reader->cursor + 1;
			reader->rest = ft_memcpy(reader->rest, reader->buff + reader->cursor,\
				(ret - reader->cursor + 1));
			ft_strdel(&start);
			return (0);
		}
		if (instruction_decoder(reader, start, output))
		{
			ft_strdel(&start);
			return (1);
		}
	}
	ft_strdel(&start);
	ft_strdel(&(reader->rest));
	return (0);
}



static int	decoder_dasm(int fd, char **output)
{
	int			inst_size;
	int			ret;
	t_reader	reader;

	reader.rest = NULL;
	reader.col = 0;
	if ((ret = header_decoder(output, &inst_size, fd)))
		return (ret);
	reader.nb_chars = 2192;
	while ((ret = read(fd, reader.buff, BUFF_SIZE_ASM)))
	{
		reader.cursor = 0;
		if (ret == -1)
		{
			ft_strdel(&(reader.rest));
			return (-1);
		}
		if ((ret = buff_manager_dasm(&reader, output, ret)))
			return (ret);
		reader.nb_chars += ret;
	}
	ret = 0;
	ret = instruction_decoder(&reader, reader.rest, output);
	ft_strdel(&(reader.rest));
	return (reader.nb_chars != inst_size ? 1 : ret);
}

static int		writer_dasm(char *output, char *file_name)
{
	int i;
	int fd;

	i = -1;
	while (file_name[++i])
		if (file_name[i] == '.')
			break ;
	file_name[i] = 0;
	if (!(file_name = ft_strjoin(file_name, ".s")))
		return (1);
	if ((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC,\
					S_IRUSR | S_IWUSR)) == -1)
	{
		ft_strdel(&file_name);
		return (1);
	}
	write(fd, output, ft_strlen(output));
	write(1, "Writing assembler program to ", 26);
	write(1, file_name, ft_strlen(file_name));
	write(1, "\n", 1);
	ft_strdel(&file_name);
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
	if ((ret = decoder_dasm(fd, &output)))
	{
		ft_strdel(&(output));
		return (ret == -1 ? print_sys_error(errno) : 1);
	}
	ret = writer_dasm(output, av[1]);
	ft_strdel(&(output));
	return (ret ? print_sys_error(errno) : 0);
}
