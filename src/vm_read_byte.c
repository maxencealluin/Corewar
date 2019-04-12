/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:39:44 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/12 15:05:03 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include "fcntl.h"

void	init_player(t_player *player)
{
	if (!(player->header = (t_header *)malloc(sizeof(t_header) * (1))))
		exit(-1);
	// ft_bzero(player->magic, MAGIC_SIZE);
	// ft_bzero(player->name, MAGIC_SIZE);
	// ft_bzero(player->bot, MAGIC_SIZE);
	// ft_bzero(player->comm, MAGIC_SIZE);
	// ft_bzero(player->code, MAGIC_SIZE);
}

void	vm_read_byte()
{
	int fd;
	int k;
	t_player *player1;
	char *null;
	char *magic;
	char *size;

	if (!(null = (char *)malloc(sizeof(char) * (4))))
		exit(-1);
	if (!(magic = (char *)malloc(sizeof(char) * (4))))
		exit(-1);
	if (!(size = (char *)malloc(sizeof(char) * (4))))
		exit(-1);
	if (!(player1 = (t_player *)malloc(sizeof(t_player) * (1))))
		exit(-1);
	init_player(player1);
	fd = open("champs/42.cor", O_RDONLY);
	k = read(fd, magic, sizeof(unsigned int));
	player1->header->magic = (unsigned int)magic;
	k = read(fd, player1->header->prog_name, PROG_NAME_LENGTH);
	k = read(fd, null, 4);
	k = read(fd, size, sizeof(unsigned int));
	player1->header->magic = (unsigned int)size;
	k = read(fd, player1->header->comment, COMMENT_LENGTH);
	k = read(fd, null, 4);

	ft_printf("magic %d \n", magic);
	ft_printf("magic %d \n", player1->header->magic);
	ft_printf("name %s \n", player1->header->prog_name);
	ft_printf("comment %s \n", player1->header->comment);
	ft_printf("size %u \n", player1->header->prog_size);

	ft_printf("fin vm vm_read_byte\n");
	ft_memdel((void **)&magic);
	ft_memdel((void **)&size);
	ft_memdel((void **)&null);
}
