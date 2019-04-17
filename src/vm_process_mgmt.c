/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_mgmt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:42:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 19:34:42 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"

void	add_process(t_vm *vm, t_player *player)
{
	if (!(player->process = (t_process **)malloc(sizeof(t_process*))))
		return ;
	if (!(player->process[0] = (t_process *)malloc(sizeof(t_process))))
		return ;
	player->nb_process = 1;
	player->process[0]->pc = player->code_start;
	player->process[0]->carry = 0;
	player->process[0]->wait_cycles = 0;
	ft_bzero(player->process[0]->regs, REG_NUMBER * REG_SIZE);
	assign_reg(player->process[0], 0, player->player_number);
}

void	add_child_process(t_player *player, t_process *parent)
{
	if (!(player->process = (t_process **)realloc(player->process,
		sizeof(t_process *) * (player->nb_process + 1))))
		return ;
	if (!(player->process[player->nb_process] = (t_process *)realloc(player->process,
		sizeof(t_process))))
		return ;
	player->nb_process++;
	ft_memcpy((void *)player->process[player->nb_process - 1], (void *)parent,
		sizeof(parent));

}

void	create_processes(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		add_process(vm, vm->players[i++]);
	}
}
