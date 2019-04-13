/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:39:44 by fnussbau          #+#    #+#             */
/*   Updated: 2019/04/13 10:13:26 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include "fcntl.h"

void	error_champ_to_big()
{
	ft_printf("Error: Champion is too big");
	exit(0);
}

void	error_read()
{
	ft_printf("Error: reading champion code");
	exit(0);
}

void	player_code(int fd, t_player *player, t_vm *vm)
{
	char	*buff;
	char	test;
	int		res;

	if (!(buff = (char *)malloc(sizeof(char) * (CHAMP_MAX_SIZE + 1))))
		exit(-1);
	res = read(fd, buff, CHAMP_MAX_SIZE - 1);
	ft_printf("size %5d\n", res);
	res = read(fd, &test, 1);
	ft_printf("res %5d \n ", res);
	ft_printf("res %5d \n ", test == '\0');
	ft_printf("test >%s< \n", &test);
	if (res > 0 && test != '\0')
		error_champ_to_big();
	else if (res == -1)
		error_read();
	// else
	// 	place_player(buff, vm->arena);
	ft_printf("code %s ", buff);
}

void	vm_read_byte(t_player *player, t_vm *vm)
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
	ft_printf(">%08b<\n", tmp[3]);
	ft_printf(">%08b<\n", tmp[2]);
	ft_printf(">%08b<\n", tmp[1]);
	ft_printf(">%08b<\n", tmp[0]);
	// player->header->prog_size = NULL;
	// ft_printf("prog_size>%024b<\n", player->header->prog_size);
	player->header->prog_size = tmp[3] + (tmp[2] << 8) + (tmp[1] << 16) + (tmp[0] << 24);
	// ft_printf("prog_size>%024b<\n", player->header->prog_size);
	// ft_printf("prog_size>%024x<\n", player->header->prog_size);

	// player->header->prog_size = (unsigned int)tmp;
	read(fd, player->header->comment, COMMENT_LENGTH);
	read(fd, tmp, 4);
	ft_memdel((void **)&tmp);


	ft_printf("prog size %d \n", player->header->prog_size);
	player_code(fd, player, vm);
}
