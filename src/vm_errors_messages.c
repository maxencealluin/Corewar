/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 15:10:39 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void ft_error_read(char *str)
{
	ft_printf("Can't read source file %s\n", str);
	exit(-1);
}

void ft_error_too_many()
{
	ft_printf("Too many champions\n");
	exit(-1);
}

void ft_usage()
{
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	exit (-1);
}
