/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:39:59 by malluin           #+#    #+#             */
/*   Updated: 2019/04/11 17:36:41 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "op.h"
#include <time.h>

typedef struct	s_process
{
	char		regs[REG_NUMBER][REG_SIZE];
	void		*pc;
	char		carry;
}				t_process;

typedef struct	s_time
{
	clock_t 	begin;
	clock_t 	current;
	clock_t 	pause;
}				t_time;

typedef struct	s_player
{
	t_process	*process;
}				t_player;

typedef struct	s_vm {
	t_player	*players[MAX_PLAYERS];
	char		arena[MEM_SIZE];
	int			cycles;
	int			players_alive;
	int			cycle_to_die;
	int			nb_process;
	int			stop;
	int			cycle_sec;
}				t_vm;

void	refresh_window(t_vm *vm);
void	initialize_window(t_vm *vm);
void	close_window();

void	initialize_vm(t_vm *vm);
#endif
