/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:39:31 by malluin           #+#    #+#             */
/*   Updated: 2019/04/22 10:41:13 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_vm *vm, t_process *proc)
{
	int		i;

	i = 0;
	proc->last_live = vm->cycles;
	vm->number_of_live += 1;
	// LIRE NOMBRE
	// while (i < MAX_PLAYERS)
	// {
	// 	if (0 == vm->players[i++]->player_number)
	// 		vm->last_player_live = 0;
	// }
}
