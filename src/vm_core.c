/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:45:58 by malluin           #+#    #+#             */
/*   Updated: 2019/04/19 16:06:53 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>
#include <time.h>
#include "libftprintf.h"

#include "op_func.h"

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

void	pc_forward_sequence(t_vm *vm, t_process *proc) // a ecrire
{
	vm->arena[proc->pc].proc_id = 0;
	proc->pc = (proc->pc + 1) % 4096;
	vm->arena[proc->pc].proc_id = 1;
} // temp

void	pc_forward_one(t_vm *vm, t_process *proc)
{
	vm->arena[proc->pc].proc_id = 0;
	proc->pc = (proc->pc + 1) % 4096;
	vm->arena[proc->pc].proc_id = 1;
}

extern t_op op_tab[17];

void	read_op_code(t_vm *vm, t_process *proc)
{

	proc->next_op = vm->arena[proc->pc].by;
	if (proc->next_op >= 1 && proc->next_op <= 16)
		proc->wait_cycles = op_tab[proc->next_op - 1].cycles;
}

void	op_live(t_vm *vm, t_process *proc)
{
	int		i;

	i = 0;
	proc->last_live = vm->cycles;
	vm->number_of_live += 1;
	// LIRE NOMBRE 
	while (i < MAX_PLAYERS)
	{
		if (0 == vm->players[i++]->player_number)
			vm->last_player_live = 0;
	}
}

int		perform_op(t_vm *vm, t_process *proc)
{
	if (op_func[proc->next_op - 1] != NULL)
		op_func[proc->next_op - 1](vm, proc);
	else
		return (0);
	return (1);
}

void	run_process(t_vm *vm)
{
	int			res;
	t_process	*proc;

	res = 0;
	proc = vm->process;
	//inner loop
	while (proc)
	{
		// protection
		if (proc == NULL)
			continue;
		//graphic
		if (vm->arena[proc->pc].proc_id == 0)
			vm->arena[proc->pc].proc_id = 1;

		// read op code_start
		if (proc->wait_cycles == 0)
		{
			read_op_code(vm, proc);
		}
		// decrease wait cycle
		if (proc->wait_cycles != 0)
			proc->wait_cycles--;

		//act if wait cycle over
		if (proc->wait_cycles == 0)
		{
			//do action
			if (proc->next_op >= 1 && proc->next_op <= 16)
				res = perform_op(vm, proc);

			if (res == 1)
				pc_forward_sequence(vm, proc); //go forward to next instruction
			else
				pc_forward_one(vm, proc); //go forward one byte
		}
		proc = proc->next;
	}
}


void	ft_step(t_vm *vm)
{
	int		i;

	i = vm->nb_players - 1;
	//prelimiary check
	if (vm->cycles % vm->cycle_to_die == 0)
	{
		vm->current_checks++;
		// remove_dead_process(vm);
		if (vm->current_checks >= MAX_CHECKS || vm->number_of_live > NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->current_checks = 0;
		}
		vm->number_of_live = 0;
	}
	run_process(vm);
	increment_memory(vm);
	vm->cycles++;
}

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
		cycles++;
	}
}
