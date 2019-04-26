/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_perform.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:03 by malluin           #+#    #+#             */
/*   Updated: 2019/04/26 15:40:45 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "op_func.h"
#include "libftprintf.h"

extern t_op op_tab[17];

void	read_op_code(t_vm *vm, t_process *proc)
{
	proc->next_op = vm->arena[proc->pc].by;
	if (proc->next_op >= 1 && proc->next_op <= 16)
		proc->wait_cycles = op_tab[proc->next_op - 1].cycles;
}

void	pc_forward_sequence(t_vm *vm, t_process *proc)
{
	vm->arena[proc->pc].proc_id = 0;
	proc->pc = (proc->pc + proc->step_over) % MEM_SIZE;
	vm->arena[proc->pc].proc_id = 1;
	proc->step_over = 0;
}

void	pc_forward_one(t_vm *vm, t_process *proc)
{
	vm->arena[proc->pc].proc_id = 0;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	vm->arena[proc->pc].proc_id = 1;
}

void	perform_op(t_vm *vm, t_process *proc)
{
	int		res;

	res = 0;
	if (proc->next_op >= 1 && proc->next_op <= 16 && op_func[proc->next_op - 1] != NULL)
	{
		if (check_args(vm, proc, proc->next_op - 1) == 1)
		{
			if (vm->detail == 1 && proc->next_op != 16)
				ft_printf("P %4d | %s ", ft_iabs(proc->id_parent)
					, op_tab[proc->next_op - 1].op_name);
			res = op_func[proc->next_op - 1](vm, proc);
			if (res == 1)
				pc_forward_sequence(vm, proc); //go forward to next instruction
			else
				pc_forward_one(vm, proc); //go forward one byte
		}
		else
			pc_forward_sequence(vm, proc); //go forward one byte
	}
	else
		pc_forward_one(vm, proc); //go forward one byte
}
