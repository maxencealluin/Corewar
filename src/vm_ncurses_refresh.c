/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_refresh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:21 by malluin           #+#    #+#             */
/*   Updated: 2019/05/04 13:08:55 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libftprintf.h"
#define FLUO_YELLOW 100
#define FLUO_GREEN 101
#define FLUO_BLUE 102
#define FLUO_RED 103

void	initialize_color(void)
{
	start_color();
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(1);
	}
	init_color(FLUO_YELLOW, 1000, 950, 800);
	init_color(FLUO_GREEN, 650, 1000, 650);
	init_color(FLUO_BLUE, 0, 800, 1000);
	init_color(FLUO_RED, 1000, 600, 600);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(101, FLUO_YELLOW, COLOR_BLACK);//
	init_pair(111, FLUO_YELLOW, COLOR_BLACK);//
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_GREEN);
	init_pair(102, FLUO_GREEN, COLOR_BLACK);//
	init_pair(112, FLUO_GREEN, COLOR_BLACK);//
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_BLUE);
	init_pair(103, FLUO_BLUE, COLOR_BLACK);//
	init_pair(113, FLUO_BLUE, COLOR_BLACK);//
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(14, COLOR_BLACK, COLOR_RED);
	init_pair(104, FLUO_RED, COLOR_BLACK);//
	init_pair(114, FLUO_RED, COLOR_BLACK);//
	init_pair(30, COLOR_WHITE, COLOR_WHITE);
}

void	arena_display(t_vm *vm)
{
	int		i;
	int		k;

	i = 0;
	k = vm->visu.b_h + 2;
	move(k, vm->visu.b_w_l + 1);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			printw("  ");
		attron(COLOR_PAIR(ft_iabs(vm->arena[i].id) + 10 * (vm->arena[i].proc_id
			!= 0) + 100 * (vm->arena[i].st_id != 0)));//
		printw("%02hhx", vm->arena[i].by);
		attroff(COLOR_PAIR(ft_iabs(vm->arena[i].id) + 10 * (vm->arena[i].proc_id
			!= 0) + 100 * (vm->arena[i].st_id != 0)));
		printw(" ");
		i = (i % 64) * 3 + 10 > vm->visu.w_l ? i + (64 - i % 64) : i + 1;
		if (i % 64 == 0)
			move(++k, vm->visu.b_w_l + 1);
		if (i / 64 + 3 > LINES)
			break ;
	}
}

void	menu(t_vm *vm)
{
	attron(A_BOLD);
	move(vm->visu.b_h + 2, vm->visu.b_w_r + 3);
	printw("---- Welcome to COREWAR ---");
	move(vm->visu.b_h + 4, vm->visu.b_w_r + 3);
	printw("Current cycle: %d", vm->cycles + 1);
	move(vm->visu.b_h + 5, vm->visu.b_w_r + 3);
	printw("Cycle to die: %d", vm->cycle_to_die);
	move(vm->visu.b_h + 6, vm->visu.b_w_r + 3);
	printw("Players: %d", vm->nb_players);
	move(vm->visu.b_h + 7, vm->visu.b_w_r + 3);
	printw("Process: %d", vm->nb_process);
	move(vm->visu.b_h + 8, vm->visu.b_w_r + 3);
	printw("Cycle per sec: %d", vm->cycle_sec);
	move(vm->visu.b_h + 9, vm->visu.b_w_r + 3);
	printw("Number of lives: %d", vm->number_of_live);
	move(vm->visu.b_h + 10, vm->visu.b_w_r + 3);
	printw("Last player live: %d", vm->last_player_live);
	move(vm->visu.b_h + 15, vm->visu.b_w_r + 3);
	attroff(A_BOLD);
}

void	borders(t_vm *vm, int to_init)
{
	if (to_init == 1)
	{
		attron(COLOR_PAIR(30));
		attron(A_BOLD);
		if (vm->visu.boite_l != NULL)
			delwin(vm->visu.boite_l);
		if (vm->visu.boite_r != NULL)
			delwin(vm->visu.boite_r);
		vm->visu.boite_l = subwin(stdscr, vm->visu.h, vm->visu.w_l,
			vm->visu.b_h, vm->visu.b_w_l);
		vm->visu.boite_r = subwin(stdscr, vm->visu.h, vm->visu.w_r,
			vm->visu.b_h, vm->visu.b_w_r);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(30));
	}
	wborder(vm->visu.boite_l, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wborder(vm->visu.boite_r, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}

void	refresh_window(t_vm *vm)
{
	static int		line = -1;
	static int		col = -1;

	if (line != LINES || col != COLS)
	{
		clear();
		vm->visu.b_h = LINES > L_H ? (LINES - L_H) / 2 : 0;
		vm->visu.h = LINES > L_H ? L_H : LINES;
		vm->visu.b_w_l = COLS > R_W + L_W ? (COLS - R_W - L_W) / 2 : 0;
		vm->visu.w_l = COLS < L_W + R_W ? (COLS - R_W) : L_W;
		vm->visu.w_l = vm->visu.w_l < 0 ? 0 : vm->visu.w_l;
		vm->visu.b_w_r = vm->visu.w_l + vm->visu.b_w_l;
		vm->visu.w_r = COLS > R_W ? R_W : COLS;
		line = LINES;
		col = COLS;
		borders(vm, 1);
	}
	arena_display(vm);
	menu(vm);
	move(LINES - 1, COLS - 1);
	refresh();
}
