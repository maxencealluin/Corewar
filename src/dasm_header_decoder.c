/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_header_decoder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:15:04 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/13 17:51:47 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_padding(char *buff, i)
{
	int	end;

	end = i + 4;
	while (i < end)
	{
		if (buff[i])
			return (1);
		i++;
	}
	return (0);
}	

int	write_header_dasm(char *buff, char **ouput, char *command)
{
	char	*tmp;
	char	*str;
	int		ret;

	ret = 0;
	str = *output;
	if (!((tmp = ft_strdup(buff)) && (*ouput = ft_joinarg(str, ".comment", " \"", tmp, "\"\n"))))
		ret = -1;		
	ft_strdel(&tmp);
	ft_strdel(ouput);
	return (ret);
}



int	header_decoder(char **output, int *inst_size)
{
	char	*tmp;
	char	*str;
	int		ret;
	char	buff[2193];

	ret = read(fd, buff, 2192)
	if (ret != 2192)
		return (ret == -1 ? print_sys_error(errno) : 1);
	if (buff[0] != 0 || buff[1] != 0xea || buff[2] != 0x83 || buff[3] != 0xf3)
	   return (1);
	if ((check_padding(buff, 132)) || (check_padding(buffm 2187)))
		return (1);
	if (!(*output = ft_strnew(0)))
		return (-1);
	if ((write_header(buff + 4, output, ".name"))\
			|| write_header(buff + 140, output, ".comment"))
		return (-1);
	return (0);	
}
