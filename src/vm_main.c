/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 10:59:53 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 19:24:00 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"

void	read_files(t_vm *vm)
{
	int		i;

	i = 0;
	vm->nb_players = count_players(vm);
	while (i < vm->players_alive)
	{
		if (vm->players[i] != NULL)
			vm_read_byte(vm->players[i], vm);
		i++;
	}
	// fix_play_order(vm, 0, 0);
	// printf("%d %d %d %d\n\n", vm->play_order[0], vm->play_order[1], vm->play_order[2], vm->play_order[3]);
}

int		main(int ac, char **av)
{
	t_vm	*vm;

	if (ac <= 1)
		ft_usage();
	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	initialize_vm(vm);
	if (ft_parse_args(vm, ac, av) == -1)
		return (0);
	read_files(vm);
	create_processes(vm);
	ft_print_players(vm);
	// ft_print_xarena(vm, 50);
	// exit(0);
	// vm->arena[MEM_SIZE - 1].by = 255;
	if (vm->visualization == 1)
	{
		initialize_window(vm);
		main_loop(vm);
		close_window();
	}
	else
	{
		print_intro(vm);
		main_loop(vm);
	}
	return (0);
}


// initialize_window(vm);
// vm->nb_players = count_players(vm);
// if (!(vm->order = (int *)malloc(sizeof(int) * vm->nb_players)))
// 	return (NULL);
// read_files(vm);
// // ft_print_players(vm);
// // ft_printf("-----------------\n");
// pick_order(vm, vm->order);
// // exit(0);
// // ft_print_xarena(vm, 50);
// // vm->arena[MEM_SIZE - 1].by = 255;
// // print_op();
//
// main_loop(vm);
// close_window();


// void	fix_play_order(t_vm *vm, int i, int idx)
// {
// 	int		max;
// 	int		j;
// 	int		prevmax;
//
// 	i = 0;
// 	idx = 0;
// 	prevmax = 0;
// 	while (i < vm->players_alive)
// 	{
// 		j = -1;
// 		max = 0;
// 		while (++j < vm->players_alive)
// 		{
// 			if (vm->players[j]->order_arg > max && (prevmax == 0
// 				|| vm->players[j]->order_arg < prevmax))
// 			{
// 				max = vm->players[j]->order_arg;
// 				idx = j;
// 				prevmax = max;
// 			}
// 		}
// 		vm->play_order[i++] = idx;
// 	}
// }

// Surement useless fix_play_order car au final l'ordre de creation des joueurs est en fonction de leur ordre en argv
// donc suffit de boucler de facon decroissante pour avoir le bon ordre
