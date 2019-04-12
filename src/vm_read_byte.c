/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:39:44 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/12 15:29:14 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include "fcntl.h"

void	vm_read_byte(t_player *player)
{
	int fd;
	char *tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (4))))
		exit(-1);
	fd = open("champs/42.cor", O_RDONLY);
	read(fd, tmp, sizeof(unsigned int));
	player->header->magic = (unsigned int)tmp;
	read(fd, player->header->prog_name, PROG_NAME_LENGTH);
	read(fd, tmp, 4);
	read(fd, tmp, sizeof(unsigned int));
	player->header->magic = (unsigned int)tmp;
	read(fd, player->header->comment, COMMENT_LENGTH);
	read(fd, tmp, 4);
	ft_memdel((void **)&tmp);
}
