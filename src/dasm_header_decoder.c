/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_header_decoder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <ccepre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:15:04 by rkirszba          #+#    #+#             */
/*   Updated: 2019/05/13 19:13:18 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_padding(char *buff, int i)
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

static int	write_header_dasm(char *buff, char **output, char *command)
{
	char	*tmp;
	char	*str;
	int		ret;

	ret = 0;
	str = *output;
	if (!((tmp = ft_strdup(buff)) && (*output\
				= ft_strjoinarg(5, str, command, " \"", tmp, "\"\n"))))
		ret = -1;		
	ft_strdel(&tmp);
	ft_strdel(output);
	return (ret);
}



int	header_decoder(char **output, int *inst_size, int fd)
{
	int		ret;
	char	buff[2193];

	ret = read(fd, buff, 2192);
	if (ret != 2192)
		return (ret == -1 ? print_sys_error(errno) : 1);
	if (buff[0] != 0 || buff[1] != (char)234 || buff[2] != (char)131 || buff[3] != (char)243)
	   return (1);
	if ((check_padding(buff, 132)) || (check_padding(buff, 2188)))
		return (1);
	*inst_size = get_value(buff + 132, 4);
	if (!(*output = ft_strnew(0)))
		return (-1);
	if ((write_header_dasm(buff + 4, output, ".name"))\
			|| write_header_dasm(buff + 140, output, ".comment"))
		return (-1);
	return (0);	
}
