/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/04/26 15:57:01 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "vm.h"

void	ft_usage(void)
{
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
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

void	error_champ_to_big(void)
{
	ft_printf("Error: Champion is too big\n");
	exit(-2);
}

void	error_read(void)
{
	ft_printf("Error: reading champion code\n");
	exit(-2);
}

void	error_param(void)
{
	ft_printf("Error: wrong parameters in exec code\n");
}
