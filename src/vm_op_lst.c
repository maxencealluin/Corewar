/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:19:58 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/22 14:05:58 by fnussbau         ###   ########.fr       */
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

int		op_load(t_vm *vm, t_process *p)
{
	unsigned char	c;
	int				*by;
	int				count;
	char			test;

	ft_printf("load\n");
	c  = vm->arena[p->pc + 1].by;
	if (!(by = (int *)malloc(sizeof(int) * 4)))
		exit(-1);
	if (!(by = ft_decode_byte(c, by, vm)))
		exit(-1);
	// ft_printf("%d // %d // %d // %d -- %d\n", by[0], by[1], by[2], by[3], pos);
	if (is_register(by[1], vm->arena[p->pc + by[0] + 1].by) == 0)
		error_param();
	count = 0;
	while (count < by[0])
	{
		count++;
		// ft_printf("current byte[%d] value \n%02hhx\n", i, vm->arena[pos + count].by);
		p->regs[by[1]][count] = vm->arena[p->pc + count].by;
		ft_printf("in reg %02b \n", p->regs[3][count]);
	}
	test = (p->regs[by[1]][0] << 6) + (p->regs[by[1]][1] << 4) + (p->regs[by[1]][2] << 4) + (p->regs[by[1]][3]);
	// ft_printf("current byte value \n%08b\n", test);
	if (test == 0)
		p->carry = 1;
	ft_memdel((void **)&by);

	return (1);
}

/*
**first parameter must be a register
**where this operation writes it depends on the type of the second argument
** if the second parameter is an indirect (address) then it must be calculated with `% IND_MOD`
*/

void				reg_to_mem(int reg, int pos, t_vm *vm, t_process *p)
{
	int				count;

	count = 0;
	ft_print_xarena(vm, 60);
	while (count < REG_SIZE)
	{
		// ft_printf("%d\n", by[1]);
		vm->arena[pos + count].by = p->regs[reg][count];
		// vm->arena[pos + count].by = 7;
		count++;
	}
	ft_print_xarena(vm, 60);
	exit(0);


}

void				reg_to_reg(int src_reg, int dst_reg, t_process *p)
{
	int				count;

	count = 0;
	while (count < REG_SIZE)
	{
		p->regs[dst_reg][count] = p->regs[src_reg][count];
		ft_printf("reg[%d][%d] = %d\n", dst_reg, count, p->regs[src_reg][count]);
		count++;
	}
}

int		op_store(t_vm *vm, t_process *p)
{
	unsigned char	c;
	int				*by;
	int				count;
	char			test;
	int				position;
	int				i;

	i = p->pc + 1;
	c = vm->arena[p->pc].by;
	ft_printf("check the pc: %02hhx\n", c);
	ft_printf("check the pc: %08hhb\n", c);
	if (!(by = (int *)malloc(sizeof(int) * 4)))
		exit(-1);
	if (!(by = ft_decode_byte(c, by, vm)))
		exit(-1);
	ft_printf("check the by: %d\n", by[0]);
	ft_printf("check the by: %d\n", by[1]);
	ft_printf("check the by: %d\n", by[2]);
	ft_printf("check the by: %d\n", by[3]);
	if (is_register(by[0], vm->arena[p->pc + 1].by) == 0)
		error_param();
	// ft_printf("the byte: %d \n", by[1]);
	if (is_register(by[1], vm->arena[p->pc + by[0] + 1].by))
	{
		ft_printf("the register\n");
		reg_to_reg(vm->arena[p->pc + 1].by, vm->arena[p->pc + 2].by, p);
	}
	else
	{
		ft_printf("is TIND\n");
		//ecrire par dessus
		// position = read_ind();
		position = -5;
		reg_to_mem(vm->arena[p->pc + 1].by, (p->pc + position - 1 + MEM_SIZE) % MEM_SIZE, vm, p);
		count = 0;

	}
	ft_printf("here\n");
	return (1);
}
//
// void	op_add(t_vm *vm, t_process *p, int pos)
// {
// 	;
// }
//
// void	op_sub(t_vm *vm, t_process *p, int pos)
// {
// 	;
// }
