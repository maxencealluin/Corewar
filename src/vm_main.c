/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 10:59:53 by malluin           #+#    #+#             */
/*   Updated: 2019/04/15 15:04:14 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include <ncurses.h>
#include <time.h>

void	dump_memory(t_vm *vm)
{
	int i = 0;

	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", vm->arena[i++].by);
		if (i % 64 == 0)
			ft_printf("\n");
	}
}

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

void	increment_memory(t_vm *vm)
{
	static int i = -1;
	//
	// vm->arena[i++].by++;
	// if (i == 4096)
	// 	i = 0;

	if (vm->arena[++i].by == 1)
		vm->arena[i].by = (char)255;
}

void	main_loop(t_vm *vm)
{
	int		cycles;
	t_time	*time;

	if (!(time = (t_time *)malloc(sizeof(t_time))))
		exit(-1);
	time->begin = clock();
	time->pause = clock();
	cycles = 0;
	while (1)
	{
		event_handler(vm, time, &cycles);
		refresh_window(vm);
		time->current = clock();
		move(10, COLS - COLS/6);
		// printw("  %d %d ", time->current, time->begin);
		if (((time->current - time->begin) / 1000 < (unsigned long)
		(cycles * 1000 / vm->cycle_sec)) || vm->stop == 1)
			continue;

		increment_memory(vm);

		vm->cycles++;
		cycles++;
	}
}

void	read_files(t_vm *vm)
{
	int		i;

	i = 0;
	vm->nb_players = count_players(vm);
	while (i < vm->players_alive)
		vm_read_byte(vm->players[i++], vm);
	// reset nb plqyers
	vm->nb_players = count_players(vm);
}

int			count_players(t_vm *vm)
{
	int i;

	i = 0;
	while (vm->players[i] != NULL && i < MAX_PLAYERS)
		i++;
	return (i);
}

int		main(int ac, char **av)
{
	t_vm	*vm;

	if (ac <= 1)
		ft_usage();
	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	initialize_vm(vm);
	if (ft_parse_args(vm, ac, av) == -1)
		return (0);
	// dump_memory(vm);
	// initialize_window(vm);
	vm->nb_players = count_players(vm);

	read_files(vm);
	ft_print_players(vm);
	ft_printf("-----------------\n");

	pick_order(vm);
	exit(0);
	// ft_print_xarena(vm, 50);
	// vm->arena[MEM_SIZE - 1].by = 255;
	// print_op();
	// exit(0);

	// main_loop(vm);
	// close_window();
	return (0);
}
