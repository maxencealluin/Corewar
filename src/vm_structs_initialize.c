/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs_initialize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:05:00 by malluin           #+#    #+#             */
/*   Updated: 2019/04/13 09:45:12 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	initialize_player(t_player *player)
{
	player->process = NULL;
	player->code = NULL;
	if (!(player->header = (t_header *)malloc(sizeof(t_header))))
		exit(-1);
	player->header->magic = 0;
	ft_bzero(player->header->prog_name, PROG_NAME_LENGTH);
	player->header->prog_size = 0;
	ft_bzero(player->header->comment, COMMENT_LENGTH);
	player->file_path = NULL;
	player->player_number = 0;
	player->order_arg = 0;
}

void	initialize_vm(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!(vm->players[i] = (t_player *)malloc(sizeof(t_player))))
			exit(-1);
		initialize_player(vm->players[i++]);
	}
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
}
