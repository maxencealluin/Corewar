/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:12:29 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 15:15:26 by malluin          ###   ########.fr       */
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
		printf("Player: %d\n", vm->players[i]->player_number);
		printf("Order: %d\n", vm->players[i]->order_arg);
		printf("File_path: %s\n", vm->players[i]->file_path);
		printf("\n\n");
		i++;
	}
}
