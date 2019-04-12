/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:39:44 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/12 17:17:00 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include "fcntl.h"

void	vm_read_byte(t_player *player)
{
	int fd;
	unsigned char *tmp;

	if (!(tmp = (unsigned char *)malloc(sizeof(unsigned char)* (4))))
		exit(-1);
	fd = open(player->file_path, O_RDONLY);
	read(fd, tmp, sizeof(unsigned int));
	player->header->magic = tmp[3] + (tmp[2] << 8) + (tmp[1] << 16) + (tmp[0] << 24);
	read(fd, player->header->prog_name, PROG_NAME_LENGTH);
	read(fd, tmp, 4);
	read(fd, tmp, sizeof(unsigned int));
	player->header->prog_size = (unsigned int)tmp;
	read(fd, player->header->comment, COMMENT_LENGTH);
	read(fd, tmp, 4);
	ft_memdel((void **)&tmp);
}
