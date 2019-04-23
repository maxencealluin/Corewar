/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:39:31 by malluin           #+#    #+#             */
/*   Updated: 2019/04/23 18:58:17 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libftprintf.h"
#include <ncurses.h>

int		check_args(t_vm *vm, t_process *proc)
{
	// (void)(vm);
	// (void)(proc);
	return (1);
}

int		op_live(t_vm *vm, t_process *proc)
{
	int		i;
	int		nb;

	i = 0;
	proc->last_live = vm->cycles;
	vm->number_of_live += 1;
	nb = read_arena(vm, proc->pc + 1, DIR_SIZE);
	proc->step_over = 5;
	while (i < vm->nb_players)
	{
		if (vm->players[i] != NULL && nb == vm->players[i]->player_number)
		{
			vm->last_player_live = nb;
			break;
		}
		i++;
	}
	return (1);
}

int		op_fork(t_vm *vm, t_process *proc)
{
	int		arg;

	arg = read_arena(vm, proc->pc + 1, IND_SIZE);
	proc->step_over = 3;
	// printf("%d\n", (((proc->pc + arg % IDX_MOD) % 4096 + 4096) % 4096));
	add_child_process(vm, proc, ((proc->pc + arg % IDX_MOD) % 4096 + 4096)
		% 4096);
	ft_print_process(vm);
	return (1);
}

int		op_lfork(t_vm *vm, t_process *proc)
{
	int		arg;

	arg = read_arena(vm, proc->pc + 1, IND_SIZE);
	proc->step_over = 3;
	// printf("%d\n", (((proc->pc + arg) % 4096 + 4096) % 4096));
	add_child_process(vm, proc, ((proc->pc + arg) % 4096 + 4096) % 4096);
	ft_print_process(vm);
	return (1);
}

int		op_aff(t_vm *vm, t_process *proc)
{
	int		nb;

	// ft_decode_byte2(vm, vm->arena[proc->pc + 1].by);
	nb = read_arena(vm, proc->pc + 2, T_REG);
	if (nb >= 1 && nb <= 16)
	{
		nb = read_reg(proc->regs[nb - 1]);
		ft_printf("%d\n", nb);
	}
	proc->step_over = 3;
	return (1);
}
