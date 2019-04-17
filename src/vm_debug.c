/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:12:29 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 18:51:27 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include "vm.h"

void	ft_print_xstr(int size, char *str, int wid)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (i % wid == 0)
			ft_printf("\n");
		ft_printf("%02hhx ", str[i++]);

	}
	ft_printf("\n");
}

void	ft_print_xarena(t_vm *vm, int wid)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % wid == 0)
			ft_printf("\n");
		ft_printf("%02hhx ", vm->arena[i++].by);
	}
	ft_printf("\n");
}

void	ft_print_process(t_player *play)
{
	int		i;
	int		j;

	i = 0;
	while (play != NULL && i < play->nb_process)
	{
		j = 0;
		ft_printf("Process %2d\n", i);
		ft_printf("PC %p\n", play->process[i]->pc);
		ft_printf("carry %d\n", play->process[i]->carry);
		while (j < REG_NUMBER)
		{
			ft_printf("reg %d: %d\n", j, read_reg(play->process[i]->regs[j]));
			// ft_printf("%hhd %hhd %hhd %hhd\n", play->process[i]->regs[j][0], play->process[i]->regs[j][1], play->process[i]->regs[j][2], play->process[i]->regs[j][3]);
			j++;
		}
		i++;
	}
}

void	ft_print_players(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->players_alive)
	{
		ft_printf("Player: %d\n", vm->players[i]->player_number);
		ft_printf("Order: %d\n", vm->players[i]->order_arg);
		ft_printf("File_path: %s\n", vm->players[i]->file_path);
		ft_printf("Magic: %07x\n", vm->players[i]->header->magic);
		ft_printf("prog_name: %s\n", vm->players[i]->header->prog_name);
		ft_printf("comment: %s\n", vm->players[i]->header->comment);
		ft_print_process(vm->players[i]);
		ft_printf("\n\n");
		i++;
	}

	ft_printf("---------- ARENA ----------\n");
	ft_printf("%p\n", vm->arena);
	ft_printf("%s\n", vm->arena);
}

void	increment_memory(t_vm *vm)
{
	static int i = 0;

	vm->arena[i++].by++;
	if (i == 4096)
		i = 0;
}
