/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/05/03 13:28:47 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "vm.h"

void	ft_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N -v N | -g] [[-n N] <champion1.cor>]");
	ft_printf(" <...>\n");
	ft_printf("#### TEXT OUTPUT MODE #######################\n");
	ft_printf("-dump N: Dumps memory after N cycles then exits\n");
	ft_printf("-v    N: Verbosity levels, can be added ");
	ft_printf("together to enable several:\n");
	ft_printf("	- 0 : Show only essentials\n");
	ft_printf("	- 1 : Show lives\n");
	ft_printf("	- 2 : Show cycles\n");
	ft_printf("	- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("	- 8 : Show deaths\n");
	ft_printf("	- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("	- 32 : Show Cycles_to_die changes\n");
	ft_printf("#### NCURSES OUTPUT MODE #######################\n");
	ft_printf("-g    : Ncurses output mode\n");
	exit(-1);
}

void	ft_error_read(t_vm *vm, char *str)
{
	ft_printf("Can't read source file %s\n", str);
	free_structs(vm);
	exit(-1);
}

void	ft_error_too_many(t_vm *vm)
{
	ft_printf("Too many champions\n");
	free_structs(vm);
	exit(-1);
}

void	ft_incorrect_number(t_vm *vm)
{
	ft_printf("The provided number is incorrect");
	ft_printf(", please provide a positive integer.\n");
	free_structs(vm);
	exit(-1);
}

void	ft_error_already_assigned(t_vm *vm)
{
	ft_printf("Two champions can't have the same number");
	ft_printf(", please provide another positive integer.\n");
	free_structs(vm);
	exit(-1);
}
