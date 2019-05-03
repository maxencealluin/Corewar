/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_byte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnussbau <fnussbau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:39:44 by fnussbau          #+#    #+#             */
/*   Updated: 2019/05/03 17:10:17 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include "fcntl.h"

void	put_player(t_vm *vm, t_player *player, unsigned char *buff, int idx)
{
	unsigned int	i;
	int				zero;
	static int		nb_players = 5;

	i = 0;
	nb_players = nb_players == 5 ? vm->nb_players : nb_players;
	if (vm->players_alive == 0)
		return ;
	zero = MEM_SIZE / vm->players_alive * (vm->players_alive - nb_players--);
	player->code_start = zero;
	while (i < CHAMP_MAX_SIZE && i < player->header->prog_size)
	{
		ft_memmove(&vm->arena[zero + i].by, &buff[i], 1);
		vm->arena[zero + i].id = idx;
		i++;
	}
}

void	check_errors(t_player *player, unsigned char *buff, int res, char test)
{
	if (player->header->magic != 15369203)
	{
		ft_memdel((void **)&buff);
		error_wrong_header();
	}
	else if (res > 0 && test != '\0')
	{
		ft_memdel((void **)&buff);
		error_champ_to_big();
	}
	else if (res == -1)
	{
		ft_memdel((void **)&buff);
		error_read();
	}
}

void	read_player_code(int fd, t_player *player, t_vm *vm)
{
	unsigned char	*buff;
	char			test;
	int				res;

	if (!(buff = (unsigned char *)malloc(sizeof(unsigned char)
		* (CHAMP_MAX_SIZE + 1))))
		exit(-1);
	ft_bzero(buff, CHAMP_MAX_SIZE);
	res = read(fd, buff, CHAMP_MAX_SIZE);
	if (res != (int)player->header->prog_size)
		error_wrong_weight();
	res = read(fd, &test, 1);
	if (player->header->magic != 15369203 || (res > 0 && test != '\0')
		|| res == -1)
		check_errors(player, buff, res, test);
	else
	{
		put_player(vm, player, buff, player->player_number);
		ft_memdel((void **)&buff);
	}
}

void	vm_read_byte(t_player *player, t_vm *vm)
{
	int				fd;
	unsigned char	*tmp;

	if (!(tmp = (unsigned char *)malloc(sizeof(unsigned char) * (4))))
		exit(-1);
	fd = open(player->file_path, O_RDONLY);
	read(fd, tmp, sizeof(unsigned int));
	player->header->magic = tmp[3] + (tmp[2] << 8) + (tmp[1] << 16)
		+ (tmp[0] << 24);
	read(fd, player->header->prog_name, PROG_NAME_LENGTH);
	read(fd, tmp, 4);
	read(fd, tmp, sizeof(unsigned int));
	player->header->prog_size = tmp[3] + (tmp[2] << 8) + (tmp[1] << 16)
		+ (tmp[0] << 24);
	read(fd, player->header->comment, COMMENT_LENGTH);
	read(fd, tmp, 4);
	ft_memdel((void **)&tmp);
	read_player_code(fd, player, vm);
}
