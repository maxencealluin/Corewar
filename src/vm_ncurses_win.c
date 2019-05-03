/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:31 by malluin           #+#    #+#             */
/*   Updated: 2019/05/03 11:45:57 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>

void	initialize_window(t_vm *vm)
{
	initscr();
	initialize_color();
	cbreak();
	nodelay(stdscr, TRUE);
	noecho();
	keypad(stdscr, TRUE);
	refresh_window(vm);
}

void	close_window(t_vm *vm)
{
	delwin(vm->visu.boite_l);
	delwin(vm->visu.boite_r);
	endwin();
}
