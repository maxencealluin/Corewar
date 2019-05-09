/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 17:06:50 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void	error_wrong_header(void)
{
	ft_printf("Error: File has an invalid header\n");
	exit(-2);
}

void	error_wrong_weight(void)
{
	ft_printf("Error: File has a code size");
	ft_printf(" that differs from what its header says\n");
	exit(-2);
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
