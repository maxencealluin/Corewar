/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_refresh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:21 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 12:06:43 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm.h"
#include "libft.h"

void	arena_display(t_vm *vm)
{
	int i = 0;

	// attron(A_BOLD);
	move(2,0);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			printw("	");
		printw("%02x ", vm->arena[i++]);
		if (i % 64 == 0)
			printw("\n");
	}
	// attroff(A_DIM);
}

void	menu(t_vm *vm)
{
	attron(A_BOLD);
	move(2, COLS - COLS/6);
	printw("---- Welcome to COREWAR ---");
	move(4, COLS - COLS/6);
	printw("Cycle passed: %d\n", vm->cycles);
	move(5, COLS - COLS/6);
	printw("Cycle to die: %d\n", vm->cycle_to_die);
	move(6, COLS - COLS/6);
	printw("Players alive: %d", vm->players_alive);
	move(7, COLS - COLS/6);
	printw("Process: %d", vm->nb_process);
	move(8, COLS - COLS/6);
	printw("Cycle per sec: %d", vm->cycle_sec);
	attroff(A_BOLD);
}

void 	borders()
{
	WINDOW *boite;


	attron(COLOR_PAIR(1));
	border('|', '|', '-', '-', '+', '+', '+', '+');
	// box(boite, ACS_VLINE, ACS_HLINE);
	boite = subwin(stdscr, LINES, COLS * 1 / 4, 0, COLS - COLS / 4);
	wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
	// box(boite, ACS_VLINE, ACS_HLINE);
	ft_memdel((void **)&boite);
	attroff(COLOR_PAIR(1));
}

void	refresh_window(t_vm *vm)
{
	arena_display(vm);
	menu(vm);
	borders();
	move(LINES - 1,COLS - 1);
	refresh();
	// getch();
}
