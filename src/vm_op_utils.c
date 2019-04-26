/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 10:20:14 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/26 11:58:50 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libftprintf.h"

int		*ft_decode_byte(t_vm *vm, unsigned char c, int *tab)
{
	tab[0] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[1] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[2] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[3] = vm->enc[(c >> 6)];
	return (tab);
}

void	ft_decode_byte2(t_vm *vm, unsigned char c)
{
	vm->enc_byte[0] = vm->enc[(c >> 6) & 3];
	vm->enc_byte[1] = vm->enc[(c >> 4) & 3];
	vm->enc_byte[2] = vm->enc[(c >> 2) & 3];
	vm->enc_byte[3] = vm->enc[c & 3];
	if (vm->debug == 1)
		ft_printf("\n Encoding byte: ||%b %b %b %b ||\n", vm->enc_byte[0], vm->enc_byte[1], vm->enc_byte[2], vm->enc_byte[3]);
}

void	ft_decode_byte_codes(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (vm->enc_byte[i] == IND_SIZE)
			vm->enc_byte_codes[i] = T_IND;
		else if (vm->enc_byte[i] == DIR_SIZE)
			vm->enc_byte_codes[i] = T_DIR;
		else if (vm->enc_byte[i] == REG_SIZE)
			vm->enc_byte_codes[i] = T_REG;
		i++;
	}
	if (vm->debug == 1)
		ft_printf("\n Encoding byte codes: ||%b %b %b %b ||\n", vm->enc_byte_codes[0], vm->enc_byte_codes[1], vm->enc_byte_codes[2], vm->enc_byte_codes[3]);
}

// int		*ft_decode_byte(t_vm *vm, unsigned char c, int *tab)
// {
// 	tab[0] = vm->enc[(c >> 6)];
// 	c = (c << 2);
// 	tab[1] = vm->enc[(c >> 6)];
// 	c = (c << 4);
// 	tab[2] = vm->enc[(c >> 6)];
// 	c = (c << 6);
// 	tab[3] = vm->enc[(c >> 6)];
// 	return (tab);
// }

int		is_register(int decoded_by, unsigned char arena_by)
{

	if (decoded_by != 1 || arena_by > 16 || arena_by <= 0)
	{
		// ft_printf("into the byte: %d \n", decoded_by);
		// ft_printf("arena byte: %d \n", arena_by);
		return (0);
	}
	return (1);
}

void				reg_to_reg(int src_reg, int dst_reg, t_process *p)
{
	int				count;

	count = 0;
	while (count < REG_SIZE)
	{
		p->regs[dst_reg][count] = p->regs[src_reg][count];
		// ft_printf("reg[%d][%d] = %d\n", dst_reg, count, p->regs[src_reg][count]);
		count++;
	}
}

void				reg_to_mem(t_vm *vm, t_process *p, int reg, int pos)
{
	int				count;

	count = 0;
	while (count < REG_SIZE)
	{
		vm->arena[pos + count].by = p->regs[reg][count];
		count++;
	}
}

// void				mem_to_reg(int reg, int pos, t_vm *vm, t_process *p)
// {
// 	int				count;
//
// 	count = 0;
// 	while (count < REG_SIZE)
// 	{
// 		// ft_printf("%d\n", by[1]);
// 		// vm->arena[pos + count].by = p->regs[reg][count];
// 		// vm->arena[pos + count].by = 7;
// 		count++;
// 	}
// }
