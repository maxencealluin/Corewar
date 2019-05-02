/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors_messages_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:13 by malluin           #+#    #+#             */
/*   Updated: 2019/05/02 18:34:45 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "vm.h"

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
