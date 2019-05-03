/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:19:58 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/03 14:01:37 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libftprintf.h"

int		op_load(t_vm *vm, t_process *p)
{
	int				res;
	int				r;

	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	r = read_arena(vm, p->pc + 2 + vm->enc_byte[0], vm->enc_byte[1]);
	if (is_register(vm->enc_byte[1], r) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	res = op_load_utils(vm, p, r, 1);
	if ((vm->detail & 4) != 0)
		ft_printf("r%d\n", r);
	p->carry = res == 0 ? 1 : 0;
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	return (1);
}

int		op_lld(t_vm *vm, t_process *p)
{
	int				res;
	int				r;

	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	r = read_arena(vm, p->pc + 2 + vm->enc_byte[0], vm->enc_byte[1]);
	if (is_register(vm->enc_byte[1], r) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	res = op_load_utils(vm, p, r, 0);
	p->carry = res == 0 ? 1 : 0;
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	if ((vm->detail & 4) != 0)
		ft_printf("r%d\n", r);
	return (1);
}

int		op_ldi(t_vm *vm, t_process *p)
{
	int				res;
	int				reg;
	int				size;
	int				k;

	k = 0;
	res = 0;
	reg = 0;
	size = 2;
	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	while (k < 2)
	{
		res = res + op_ldi_utils(vm, p, k, size);
		size = size + vm->enc_byte[k];
		k++;
	}
	reg = read_arena(vm, p->pc + size++, T_REG);
	if ((vm->detail & 4) != 0)
		ft_printf("r%d ", reg);
	assign_reg(p, reg, read_arena(vm, p->pc + (res % IDX_MOD), REG_SIZE));
	p->step_over = size;
	if ((vm->detail & 4) != 0)
		ft_printf("\n");
	return (1);
}

int		*set_enc_by(t_vm *vm, t_process *p, int *by)
{
	unsigned char	c;

	c = vm->arena[p->pc + 1].by;
	if (!(by = (int *)malloc(sizeof(int) * 4)))
		exit(-1);
	if (!(by = ft_decode_byte(vm, c, by)))
	{
		ft_memdel((void **)&by);
		exit(-1);
	}
	return (by);
}

int		op_lldi(t_vm *vm, t_process *p)
{
	int				*by;
	int				res;
	short			r;

	by = NULL;
	by = set_enc_by(vm, p, by);
	by[0] = (by[0] == 4) ? 2 : by[0];
	by[1] = (by[1] == 4) ? 2 : by[1];
	if (is_register(by[2], vm->arena[p->pc + 1 + by[0] + by[1] + 1].by) == 0)
	{
		p->step_over = by[0] + by[1] + by[2] + 2;
		ft_memdel((void **)&by);
		return (1);
	}
	res = read_arena(vm, p->pc + 1 + 1, by[0]) + read_arena(vm, p->pc + 1
		+ by[0] + 1, by[1]);
	res = read_arena(vm, p->pc + res, 1);
	r = read_arena(vm, p->pc + 1 + by[0] + 1 + by[1], by[2]);
	assign_reg(p, r, res);
	p->step_over = by[0] + by[1] + by[2] + 2;
	p->carry = 1;
	ft_memdel((void **)&by);
	if ((vm->detail & 4) != 0)
		ft_printf("\n");
	return (1);
}
