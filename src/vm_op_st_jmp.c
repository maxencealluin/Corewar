/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_st_jmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:19:58 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/02 18:48:51 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libftprintf.h"

int		op_zjmp(t_vm *vm, t_process *p)
{
	int		jump;

	jump = 0;
	jump = read_arena(vm, p->pc + 1, IND_SIZE);
	if (p->carry == 0)
	{
		p->step_over = 3;
		if ((vm->detail & 4) != 0)
			ft_printf("%d FAILED\n", jump);
		return (1);
	}
	p->step_over = jump % IDX_MOD;
	if ((vm->detail & 4) != 0)
		ft_printf("%d OK\n", p->step_over);
	return (1);
}

int		op_store(t_vm *vm, t_process *p)
{
	int				position;

	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	if (is_register(vm->enc_byte[0], vm->arena[p->pc + 2].by) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	if ((vm->detail & 4) != 0)
		ft_printf("r%d ", vm->arena[p->pc + 2].by);
	if (is_register(vm->enc_byte[1], vm->arena[p->pc + 2 + vm->enc_byte[0]].by))
	{
		reg_to_reg(vm->arena[p->pc + 2].by, vm->arena[p->pc + 2 + 1].by, p);
		if ((vm->detail & 4) != 0)
			ft_printf("r%d\n", vm->arena[p->pc + 2 + 1].by);
	}
	else
	{
		position = read_arena(vm, p->pc + 2 + vm->enc_byte[0], IND_SIZE);
		if ((vm->detail & 4) != 0)
			ft_printf("%d\n", position);
		reg_to_mem(vm, p, vm->arena[p->pc + 2].by, (p->pc + position % IDX_MOD
			+ MEM_SIZE) % MEM_SIZE);
	}
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	return (1);
}

int		op_sti(t_vm *vm, t_process *p)
{
	int				k;
	int				r;
	int				res;
	int				size;

	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	if ((vm->detail & 4) != 0)
		ft_printf("r%d ", vm->arena[p->pc + 1 + vm->enc_byte[0]].by);
	r = 0;
	res = 0;
	size = 3;
	k = 1;
	while (k < 3)
	{
		if (vm->enc_byte[k] == 1)
		{
			r = read_arena(vm, p->pc + size, T_REG);
			if (r > 0 && r <= REG_NUMBER)
				res = res + read_reg(p->regs[r - 1]);
			if ((vm->detail & 4) != 0)
				ft_printf("%d ", read_reg(p->regs[r - 1]));
		}
		else if (vm->enc_byte[k] == 2)
		{
			r = read_arena(vm, p->pc + size, IND_SIZE);
			res = res + read_arena(vm, p->pc + r, REG_SIZE);
			if ((vm->detail & 4) != 0)
				ft_printf("%d ", read_arena(vm, p->pc + r, REG_SIZE));
		}
		else if (vm->enc_byte[k] == 4)
		{
			vm->enc_byte[k] = 2;
			res = res + read_arena(vm, p->pc + size, DIR_SIZE / 2);
			if ((vm->detail & 4) != 0)
				ft_printf("%d ", read_arena(vm, p->pc + size, DIR_SIZE / 2));
		}
		size = size + vm->enc_byte[k];
		k++;
	}
	reg_to_mem(vm, p, vm->arena[p->pc + 2].by, p->pc + res % IDX_MOD);
	if ((vm->detail & 4) != 0)
		ft_printf("\n");
	p->step_over = vm->enc_byte[0] + vm->enc_byte[1] + vm->enc_byte[2] + 2;
	return (1);
}
