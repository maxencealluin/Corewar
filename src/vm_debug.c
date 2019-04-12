/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:12:29 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 16:08:48 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include "vm.h"

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
		ft_printf("\n\n");
		i++;
	}
}
