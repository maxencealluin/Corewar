/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:39:31 by malluin           #+#    #+#             */
/*   Updated: 2019/05/02 13:47:03 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libftprintf.h"
#include <ncurses.h>

extern t_op op_tab[17];

int		check_args(t_vm *vm, t_process *proc, int op)
{
	int		i;
	int		quit;
	int		size;
	int		res;

	i = 0;
	quit = 0;
	size = 2;
	if (op_tab[op].encoding == 0)
		return (1);
	ft_decode_byte2(vm, vm->arena[proc->pc + 1].by);
	ft_decode_byte_codes(vm);
	while (i < op_tab[op].nb_args)
	{
		if ((vm->enc_byte_codes[i] & op_tab[op].args_size[i]) == 0)
			quit = 1;
		else if (vm->enc_byte[i] == T_REG)
		{
			res = read_arena(vm, proc->pc + size, T_REG);
			quit = (res < 1 || res > REG_NUMBER) ? 1 : quit;
		}
		if (vm->enc_byte[i] == DIR_SIZE)
			size += (vm->enc_byte[i] - 2 * op_tab[op].size_direct);
		else
			size += vm->enc_byte[i];
		i++;
	}
	proc->step_over = size;
	// if (quit == 1)
		// printf("FAIL %d\n", proc->next_op);
	return (!quit);
}

// while (i < 3)
// {
// 	if (vm->enc_byte[i] == T_REG)
// 	{
// 		r[i] = read_arena(vm, proc->pc + size, T_REG);
// 		if (r[i] >= 1 && r[i] <= 16 && i != 2)
// 			r[i] = read_reg(proc->regs[r[i] - 1]);
// 	}
// 	else if (vm->enc_byte[i] == DIR_SIZE)
// 		r[i] = read_arena(vm, proc->pc + size, DIR_SIZE);
// 	else if (vm->enc_byte[i] == IND_SIZE)
// 	{
// 		r[i] = read_arena(vm, proc->pc + size, IND_SIZE);
// 		r[i] = read_arena(vm, proc->pc + r[i] % IDX_MOD, DIR_SIZE);
// 	}
// 	size += vm->enc_byte[i++];
// }

int		op_live(t_vm *vm, t_process *proc)
{
	int		i;
	int		nb;

	i = 0;
	proc->last_live = vm->cycles;
	vm->number_of_live += 1;
	nb = read_arena(vm, proc->pc + 1, DIR_SIZE);
	proc->step_over = 5;
	if ((vm->detail & 4) != 0)
		ft_printf("%d\n", nb);
	while (i < vm->nb_players)
	{
		if (vm->players[i] != NULL && nb == vm->players[i]->player_number)
		{
			vm->last_player_live = nb;
			if (vm->ncurses == 0 && (vm->detail & 1) != 0)
				ft_printf("Player %d (%s) is said to be alive.\n",
				vm->players[i]->player_number,
				vm->players[i]->header->prog_name);
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
	add_child_process(vm, proc, ((proc->pc + arg % IDX_MOD) % MEM_SIZE + MEM_SIZE)
		% MEM_SIZE);
	ft_print_process(vm);
	if ((vm->detail & 4) != 0)
		ft_printf("%d (%d)\n", arg, proc->pc + arg % IDX_MOD);
	return (1);
}

int		op_lfork(t_vm *vm, t_process *proc)
{
	int		arg;

	arg = read_arena(vm, proc->pc + 1, IND_SIZE);
	proc->step_over = 3;
	add_child_process(vm, proc, ((proc->pc + arg) % MEM_SIZE + MEM_SIZE) % MEM_SIZE);
	ft_print_process(vm);
	if ((vm->detail & 4) != 0)
		ft_printf("%d (%d)\n", arg, proc->pc + arg);
	return (1);
}


 // AAA CHANGER EN VALEUR ASCII

int		op_aff(t_vm *vm, t_process *proc)
{
	int		nb;

	nb = read_arena(vm, proc->pc + 2, T_REG);
	if (nb >= 1 && nb <= REG_NUMBER)
	{
		nb = read_reg(proc->regs[nb - 1]);
		if (vm->ncurses == 0)
			ft_printf("Aff: value: %d ascii: %c\n", nb, nb % 256);
	}
	proc->step_over = 3;
	return (1);
}
