/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:40:32 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/24 13:10:54 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_error_asm(int	error_id)
{
	if (error_id == 1)
		write(1, "usage\n", 6);
	return (1);
}

int		main(int ac, char **av)
{
	int		fd;
	int		i;
	t_token	*tokens;
	t_instr	*instructions;

	tokens = NULL;
	instructions = NULL;
	if (ac < 2)
		return(print_error_asm(1));
	if ((fd = open(av[ac - 1], O_RDONLY) == -1))
		return (print_error_asm(2));
	if (scanner_asm(fd, &tokens) <= 0 /*|| parser_asm(tokens, instructions) <= 0
										|| !encoder_asm(instructions)  */)
	{
		free_manager(tokens, instructions);
		return (1);
	}
	return(0);
}	
