/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:45:58 by malluin           #+#    #+#             */
/*   Updated: 2019/05/02 18:33:51 by malluin          ###   ########.fr       */
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
				vm->cycle_sec = vm->cycle_sec >= 595 ? 600 : vm->cycle_sec + 5;
			else if (ch == KEY_LEFT)
				vm->cycle_sec = vm->cycle_sec <= 5 ? 1 : vm->cycle_sec - 5;
			reset_time(time, cycles);
		}
	}
}

void	run_process(t_vm *vm)
{
	t_process	*proc;

	proc = vm->process;
	while (proc)
	{
		if (proc == NULL)
			continue;
		if (vm->arena[proc->pc].proc_id == 0)
			vm->arena[proc->pc].proc_id = 1;
		if (proc->wait_cycles == 0)
			read_op_code(vm, proc);
		if (proc->wait_cycles != 0)
			proc->wait_cycles--;
		if (proc->wait_cycles == 0)
			perform_op(vm, proc);
		proc = proc->next;
	}
}

void	ft_step(t_vm *vm)
{
	int				i;
	static int		last_check = 0;

	i = vm->nb_players - 1;
	if (vm->cycles >= last_check + vm->cycle_to_die)
	{
		vm->current_checks++;
		remove_dead_process(vm);
		if (vm->current_checks >= MAX_CHECKS || vm->number_of_live > NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			if ((vm->detail & 32) != 0)
				ft_printf("Cycles_to_die is now %d\n", vm->cycle_to_die);
			vm->current_checks = 0;
		}
		vm->number_of_live = 0;
		last_check = vm->cycles;
	}
	run_process(vm);
	vm->cycles++;
}

void	main_loop(t_vm *vm)
{
	int		cycles;
	t_time	*time;

	if (!(time = (t_time *)malloc(sizeof(t_time))))
		exit(-1);
	reset_time(time, &cycles);
	while (vm->nb_process > 0 && vm->cycle_to_die > 0)
	{
		if (vm->cycles == vm->dump_cycle)
		{
			dump_memory(vm);
			ft_print_process(vm);
			break ;
		}
		if (vm->ncurses == 1)
		{
			event_handler(vm, time, &cycles);
			refresh_window(vm);
			time->current = clock();
			move(10, COLS - COLS / 6);
			if (((time->current - time->begin) / 1000 < (unsigned long)
			(cycles * 1000 / vm->cycle_sec)) || vm->stop == 1)
				continue;
		}
		ft_step(vm);
		if ((vm->detail & 2) != 0 && vm->nb_process > 0)
			ft_printf("It is now cycle %d\n", vm->cycles);
		cycles++;
	}
	ft_memdel((void**)&time);
	end_game(vm);
}
