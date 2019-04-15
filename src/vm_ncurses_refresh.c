/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_refresh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:21 by malluin           #+#    #+#             */
/*   Updated: 2019/04/15 18:21:15 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm.h"
#include "libft.h"

void	arena_display(t_vm *vm)
{
	int i = 0;
	int col = 0;
	char by = 0;

	// attron(A_BOLD);
	move(2,0);
	while (i < MEM_SIZE)
	{
		if (has_colors() == FALSE)
		{
			endwin();
			printf("Your terminal does not support color\n");
			exit(1);
		}
		start_color();
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_YELLOW, COLOR_GREEN);
		init_pair(2, COLOR_CYAN, COLOR_BLUE);
		init_pair(3, COLOR_BLACK, COLOR_WHITE);
		init_pair(4, COLOR_RED, COLOR_MAGENTA);
		if (i % 64 == 0)
			printw("	");
		attron(COLOR_PAIR(vm->arena[i].id));
		printw("%02hhx ", vm->arena[i].id);
		attroff(COLOR_PAIR(vm->arena[i].id));
		i++;
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


	attron(COLOR_PAIR(0));
	border('|', '|', '-', '-', '+', '+', '+', '+');
	// box(boite, ACS_VLINE, ACS_HLINE);
	boite = subwin(stdscr, LINES, COLS * 1 / 4, 0, COLS - COLS / 4);
	wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
	// box(boite, ACS_VLINE, ACS_HLINE);
	ft_memdel((void **)&boite);
	attroff(COLOR_PAIR(0));
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
