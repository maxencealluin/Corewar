/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:19:58 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/01 16:23:14 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libftprintf.h"

/*
**second parameter must be a register
**change carry to one if first parameter is 0
**set the new carry
*/

// int * by ? tu peux directement utiliser vm->enc pour contenir le decodage

int		op_load(t_vm *vm, t_process *p)
{
	int				res;
	int				r;

	res = 0;
	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	r = read_arena(vm, p->pc + 2 + vm->enc_byte[0], vm->enc_byte[1]);
	if (is_register(vm->enc_byte[1], r) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	if (vm->enc_byte[0] == DIR_SIZE)
	{
		res = read_arena(vm, (p->pc + 2), DIR_SIZE);
		assign_reg(p, r, res);
	}
	else if (vm->enc_byte[0] == IND_SIZE)
	{
		res = read_arena(vm, (p->pc + 2) % IDX_MOD, IND_SIZE);
		res = read_arena(vm, p->pc + res, DIR_SIZE);
		assign_reg(p, r, res);
	}
	p->carry = res == 0 ? 1 : 0;
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	return (1);
}


int		op_lld(t_vm *vm, t_process *p)
{
	int				res;
	int				r;

	res = 0;
	ft_decode_byte2(vm, vm->arena[p->pc + 1].by);
	r = read_arena(vm, p->pc + 2 + vm->enc_byte[0], vm->enc_byte[1]);
	if (is_register(vm->enc_byte[1], r) == 0)
	{
		p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
		return (1);
	}
	if (vm->enc_byte[0] == DIR_SIZE)
	{
		res = read_arena(vm, (p->pc + 2), DIR_SIZE);
		assign_reg(p, r, res);
	}
	else if (vm->enc_byte[0] == IND_SIZE)
	{
		res = read_arena(vm, (p->pc + 2), IND_SIZE);
		res = read_arena(vm, p->pc + res, DIR_SIZE);
		assign_reg(p, r, res);
	}
	p->carry = res == 0 ? 1 : 0;
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	return (1);
}

/*
**first parameter must be a register
**where this operation writes it depends on the type of the second argument
** if the second parameter is an indirect (address) then it must be calculated with `% IND_MOD`
*/
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
		reg_to_mem(vm, p, vm->arena[p->pc + 2].by, (p->pc + position % IDX_MOD + MEM_SIZE) % MEM_SIZE);
	}
	p->step_over = 2 + vm->enc_byte[0] + vm->enc_byte[1];
	return (1);
}

/*
**does not change carry (checked with vm)
**parameter must not be a register --> asm to do it
*/
int		op_zjmp(t_vm *vm, t_process *p)
{
	int		jump;

	jump = 0;
	if (p->carry == 0)
	{
		p->step_over = 3;
		return (1);
	}
	jump = read_arena(vm, p->pc + 1, IND_SIZE);
	p->step_over = jump % IDX_MOD;
	if ((vm->detail & 4) != 0)
		ft_printf("%d (OK)\n", p->step_over);
	return (1);
}

/*
** ldi %44, %1, r2´ then the manipulation will be 44 + 1 = 45
** we will go get the value from address 45 and load it to our register r2.
** The last argument must be a register.
*/

int		op_ldi(t_vm *vm, t_process *p)
{
	unsigned char	c;
	int				*by;
	int				i;
	int				res;
	short			r;
	int				reg;

	i = p->pc + 1;
	c = vm->arena[i].by;
	res = 0;
	reg = 0;
	if (!(by = (int *)malloc(sizeof(int) * 4)))
		exit(-1);
	if (!(by = ft_decode_byte(vm, c, by)))
		exit(-1);
	by[0] = (by[0] == 4) ? 2 : by[0];
	by[1] = (by[1] == 4) ? 2 : by[1];
	ft_decode_byte2(vm, c);
	// ft_printf("byte : %d / %d\n", vm->enc_byte[0], by[0]);
	// ft_printf("byte : %d / %d\n", vm->enc_byte[1], by[1]);
	// ft_printf("byte : %d / %d\n", vm->enc_byte[2], by[2]);
	// ft_printf("byte : %d / %d\n", vm->enc_byte[3], by[3]);
	// exit(0);
	if (is_register(by[2], vm->arena[i + by[0] + by[1] + 1].by) == 0)
	{
		p->step_over = by[0] + by[1] + by[2] + 2;
		return (1);
	}
	// int k = 0;
	// while (k < 2)
	// {
	// 	if (vm->enc_byte[k] == 1)
	// 	{
	// 		r = read_arena(vm, p->pc + 2, T_REG);
	// 		res = res + read_reg(p->regs[r]);
	// 		ft_printf("res : %024b / %d\n", res, T_REG);
	// 		exit(0);
	// 	}
	// 	else if (vm->enc_byte[k] == 2)
	// 	{
	//
	// 	}
	// 	else if (vm->enc_byte[k] == 4)
	// 	{
	//
	// 	}
	// 	k++;
	//
	// }
	reg = read_arena(vm, p->pc + 2 + by[0] + by[1], T_REG);
	// ft_printf("reg : %d / %d\n", reg, T_REG);
	// exit(0);
	assign_reg(p, reg, res);

	res = read_arena(vm, i + 1, by[0]) + read_arena(vm, i + by[0] + 1, by[1]);
	res = read_arena(vm, p->pc + res % IDX_MOD + MEM_SIZE, 1);
	r = read_arena(vm, i + by[0] + 1 + by[1], by[2]);
	assign_reg(p, r, res);
	p->step_over = by[0] + by[1] + by[2] + 2;
	ft_memdel((void **)&by);
	return (1);
}


int		op_lldi(t_vm *vm, t_process *p)
{
	unsigned char	c;
	int				i;
	int				*by;
	int				res;
	short			r;

	i = p->pc + 1;
	c = vm->arena[i].by;
	if (!(by = (int *)malloc(sizeof(int) * 4)))
		exit(-1);
	if (!(by = ft_decode_byte(vm, c, by)))
		exit(-1);
	by[0] = (by[0] == 4) ? 2 : by[0];
	by[1] = (by[1] == 4) ? 2 : by[1];
	if (is_register(by[2], vm->arena[i + by[0] + by[1] + 1].by) == 0)
	{
		p->step_over = by[0] + by[1] + by[2] + 2;
		return (1);
	}
	res = read_arena(vm, i + 1, by[0]) + read_arena(vm, i + by[0] + 1, by[1]);
	res = read_arena(vm, p->pc + res, 1);
	r = read_arena(vm, i + by[0] + 1 + by[1], by[2]);
	assign_reg(p, r, res);
	p->step_over = by[0] + by[1] + by[2] + 2;
	p->carry = 1;
	ft_memdel((void **)&by);
	return (1);
}




int		op_sti(t_vm *vm, t_process *p)
{
	unsigned char	c;
	int				i;
	int				k;
	int				pos;
	int				t[4];

	i = p->pc + 1;
	c = vm->arena[i].by;
	i++;
	k = 3;
	while (k >= 0)
	{
		t[k] = c & 3;
		k--;
		c = c >> 2;
	}
	if ((vm->detail & 4) != 0)
		ft_printf("r%d", vm->arena[p->pc + 1 + t[0]].by);
	pos = find_pos(vm, p, t);
	reg_to_mem(vm, p, vm->arena[p->pc + 1 + t[0]].by, (p->pc + pos + MEM_SIZE) % IDX_MOD);
	p->step_over = p->pc + 2 + t[0] + t[1] + t[2];
	return (1);
}
