/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:45:58 by malluin           #+#    #+#             */
/*   Updated: 2019/04/18 18:59:42 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>
#include <time.h>
#include "libftprintf.h"

void	reset_time(t_time *time, int *cycles)
{
	time->begin = clock();
	time->pause = clock();
	*cycles = 0;
}

void	event_handler(t_vm *vm, t_time *time, int *cycles)
{
	int ch;

	if ((ch = getch()) != ERR)
	{
		if (ch == ' ')
		{
			vm->stop = !(vm->stop);
			if (vm->stop == 0)
				time->begin += clock() - time->pause;
			else
				time->pause = clock();
		}
		else if (ch == KEY_RIGHT || ch == KEY_LEFT)
		{
			if (ch == KEY_RIGHT)
				vm->cycle_sec = vm->cycle_sec >= 590 ? 600 : vm->cycle_sec + 10;
			else if (ch == KEY_LEFT)
				vm->cycle_sec = vm->cycle_sec <= 10 ? 1 : vm->cycle_sec - 10;
			reset_time(time, cycles);
		}
	}
}

void	process_forward(t_vm *vm, t_player *player, int idx)
{
	t_case	*place;

	place = (t_case *)player->process[idx]->pc;
	if (place == NULL)
		return ;
	place->proc_id = 0;
	if (player->process[idx]->pc == &(vm->arena[4095]))
		player->process[idx]->pc = vm->arena;
	else
		player->process[idx]->pc += sizeof(t_case);
	place = (t_case *)player->process[idx]->pc;
	place->proc_id = 1;
}

void	run_process(t_vm *vm, t_player *player)
{
	int		i;
	t_case	*place;

	i = 0;
	while (i < player->nb_process)
	{
		place = (t_case *)player->process[i]->pc;
		if (place->proc_id == 0)
			place->proc_id = 1;
		// set the op code
		if (player->process[i]->wait_cycles != 0)
			player->process[i]->wait_cycles--;
		if (player->process[i]->wait_cycles == 0)
		{
			process_forward(vm, player, i);
			//do action
			//go forward
		}
		i++;
	}
}

void	ft_step(t_vm *vm)
{
	int		i;

	i = vm->nb_players - 1;
	while (i >= 0)
	{
		if (vm->players[i]->alive == 1)
			run_process(vm, vm->players[i]);
		i--;
	}
	increment_memory(vm);
}

/*
** thing to do : check if 21 live ? decrease cycle to die by cycle delta
**
**
**
*/

void	main_loop(t_vm *vm)
{
	int		cycles;
	t_time	*time;

	if (!(time = (t_time *)malloc(sizeof(t_time))))
		exit(-1);
	reset_time(time, &cycles);
	while (1)
	{
		if (vm->cycles == vm->dump_cycle)
		{
			dump_memory(vm);
			break;
		}
		if (vm->visualization == 1)
		{
			event_handler(vm, time, &cycles);
			refresh_window(vm);
			time->current = clock();
			move(10, COLS - COLS/6);
			// printw("  %d %d ", time->current, time->begin);
			if (((time->current - time->begin) / 1000 < (unsigned long)
			(cycles * 1000 / vm->cycle_sec)) || vm->stop == 1)
				continue;
		}
		ft_step(vm);
		vm->cycles++;
		cycles++;
	}
}
