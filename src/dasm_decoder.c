/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_decoder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:58 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/13 17:51:46 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	buff_manager_dasm (t_reader *reader, char **output, int ret)
{
	int 	i;
	int		j;
	char	*start;
	i = -1;
	j = 0;	
	
	
	if (start = ft_memalloc(reader->col + ret))
	{
		ft_strdel(&(reader->rest));
		return (-1);
	}
	start = ft_memcpy(start, reader->rest, col);
   	start + col = ft_memcpy(start + col, reader->buff, ret);	
	ft_strdel(&(reader->rest));
	ret += col;
	while (reader->cursor < ret)
	{
		if (ret - reader->cursor < 14)
		{
			if (!(reader->rest = (char*)malloc(sizeof(char) *\
						(reader->nb_chars - reader->buffer + i + 1))))
			{
				ft_strdel(&start);
				return (-1);
			}
			reader->col = reader->nb_chars - reader->buffer + i + 1;
			reader->rest = ft_memcpy(reader->rest, &(buff[i]),\
				(reader->nb_chars - reader->buffer + i + 1));
			return (0);
		}
		if (instruction_decoder(reader, start, output))
		{
			ft_strdel(&start);
			return (1);
		}
	}
		
}



int	decoder_dasm(int fd, char **output)
{
	int			inst_size;
	int			nb_chars;
	int			ret;
	t_reader	reader;

	reader.rest = NULL;
	reader.col = 0;
	if ((ret = header_decoder(buff, output, &inst_size)))
		return (ret);
	reader.nb_chars = 2192;
	while ((ret = read(fd, reader.buff, BUFF_SIZE_ASM)))
	{
		reader.cursor = 0;
		if (nb_chars == -1)
		{
			ft_strdel(&(reader->rest));
			return (-1);
		}
		if ((ret = buff_manager_dasm(reader, output, ret)))
			return (ret);
		reader.nb_chars += ret;
	}
	ft_strdel(&(reader->rest));
	if (reader.nb_chars != inst_size)
		return (1);
	return (0);
}

int		writer_dasm(t_writer *reader, char *file_name)
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
	write(fd, reader->output, ft_strlen(reader->output));
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
	if (ret = decoder(fd, &output))
	{
		ft_strdel(&(output));
		return (ret == -1 ? print_sys_error(errno) : 1)
	}
	ret = writer_dasm(av[1], output);
	ft_strdel(&(output));
	return (ret ? print_sys_error(errno) : 0);
}
