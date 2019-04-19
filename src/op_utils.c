/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:30:27 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/19 11:04:01 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#include "libftprintf.h"

int		*ft_decode_byte(unsigned char c, int *tab, t_vm *vm)
{
	tab[0] = vm->enc[(c >> 6)];
	c = (c << 2);
	tab[1] = vm->enc[(c >> 6)];
	c = (c << 4);
	tab[2] = vm->enc[(c >> 6)];
	c = (c << 6);
	tab[3] = vm->enc[(c >> 6)];
	return (tab);
}

int		is_register(unsigned char decoded_by, unsigned char arena_by)
{
	if (decoded_by != 1 || arena_by > 16 || arena_by <= 0)
		return (0);
	ft_printf("test");
	return (1);
}
