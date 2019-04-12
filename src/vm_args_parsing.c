/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:16:01 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 15:55:04 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "libftprintf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		file_exists(char *path)
{
	int		fd;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if (read(fd, NULL, 0) == -1)
		return (0);
	close(fd);
	return (1);
}

void	add_player(t_vm *vm, char *path, int next_nb, int i)
{
	int		j;

	j = 0;
	while (vm->players[j] != NULL && j < MAX_PLAYERS)
		j++;
	if (j == MAX_PLAYERS)
		ft_error_too_many();
	if (!(vm->players[j] = (t_player *)malloc(sizeof(t_player))))
		exit (-1);
	vm->players[j]->file_path = ft_strdup(path);
	vm->players[j]->player_number = next_nb;
	vm->players[j]->order_arg = i;
	vm->players[j]->process = NULL;
	vm->players_alive += 1;
	if (!(vm->players[j]->header = (t_header *)malloc(sizeof(t_header))))
		exit(-1);
}

void	reorder_players(t_vm *vm)
{
	int		j;
	int		c;
	int		to_assign;

	to_assign = 1;
	c = 0;
	while (c < vm->players_alive)
	{
		j = 0;
		while (j < vm->players_alive)
		{
			if (vm->players[j++]->player_number == to_assign)
			{
				to_assign++;
				j = 0;
				continue;
			}
		}
		if (vm->players[c]->player_number == 0)
			vm->players[c]->player_number = to_assign;
		c++;
	}
}

int		ft_parse_args(t_vm *vm, int ac, char **av)
{
	int		i;
	int		next_nb;

	i = 1;
	next_nb = 0;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-dump") == 0)
		{
			if (i++ == ac - 1)
				ft_error_read("-dump");
			else
				vm->dump_cycle = ft_atoi(av[i++]);
		}
		else if (ft_strcmp(av[i], "-n") == 0)
		{
			if (i++ >= ac - 2)
				ft_error_read("-n");
			else
				next_nb = ft_atoi(av[i++]);
			if (file_exists(av[i]) == 0)
				ft_error_read(av[i]);
		}
		else
		{
			if (file_exists(av[i]) == 0)
				ft_error_read(av[i]);
			add_player(vm, av[i], next_nb, i);
			next_nb = 0;
			i++;
		}
	}
	reorder_players(vm);
	return (1);
}
