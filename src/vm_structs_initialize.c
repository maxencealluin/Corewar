/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs_initialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:00 by malluin           #+#    #+#             */
/*   Updated: 2019/04/15 16:32:46 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	initialize_vm(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
		vm->players[i++] = NULL;
	ft_bzero(vm->arena, MEM_SIZE);
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i].by = 0;
		vm->arena[i].id = 0;
		i++;
	}
	vm->cycles = 0;
	vm->players_alive = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_sec = 50;
	vm->nb_process = 0;
	vm->stop = 1;
	vm->number_of_live = 0;
	vm->last_player_live = 0;
	vm->dump_cycle = -1;
	vm->nb_players = 0;
}
