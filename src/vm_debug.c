/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:12:29 by malluin           #+#    #+#             */
/*   Updated: 2019/04/15 16:07:47 by fnussbau         ###   ########.fr       */
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
		ft_printf("pc: %d\n", (int)vm->players[i]->process->pc);
		ft_printf("\n\n");
		i++;
	}

	ft_printf("---------- ARENA ----------\n");
	ft_printf("%p\n", vm->arena);
	ft_printf("%s\n", vm->arena);
}
