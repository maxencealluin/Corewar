/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:07:52 by malluin           #+#    #+#             */
/*   Updated: 2019/04/24 13:44:42 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		read_arena(t_vm *vm, int pos, int size)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	if (size > 4)
		size = 4;
	else if (size <= 0)
		return (0);
	while (i < size)
	{
		res += vm->arena[(pos + i + 4096) % 4096].by << (size - i - 1) * 8;
		i++;
	}
	if (size == 2 && ((res >> 15) & 1) == 1)
		res |= 4294901760;
	return (res);
}

int		read_reg(unsigned char *str)
{
	int		i;
	int		res;

	res = 0;
	i = REG_SIZE - 1;
	while (i >= 0)
	{
		res += (str[i] << (REG_SIZE - i - 1) * 8);
		i--;
	}
	return (res);
}

void	assign_reg(t_process *process, short reg, int value)
{
	int		i;

	i = 0;
	if (reg <= 0 || reg > 16)
		return ;
	while (i < REG_SIZE)
	{
		process->regs[reg - 1][i] = 0xFF & (value >> (REG_SIZE - 1 - i) * 8);
		i++;
	}
}
