/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:07:52 by malluin           #+#    #+#             */
/*   Updated: 2019/04/18 18:59:43 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	while (i < REG_SIZE)
	{
		process->regs[reg][i] = 0xFF & (value >> (REG_SIZE - 1 - i) * 8);
		i++;
	}
}
