/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs_initialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:00 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 13:36:26 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	initialize_vm(t_vm *vm)
{
	ft_bzero(vm->arena, MEM_SIZE);
	vm->cycles = 0;
	vm->players_alive = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_sec = 50;
	vm->nb_process = 0;
	vm->stop = 1;
	vm->number_of_live = 0;
	vm->last_player_live = 0;
	vm->dump_cycle = -1;
	ft_bzero(vm->players, MAX_PLAYERS);
}
