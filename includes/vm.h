/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:39:59 by malluin           #+#    #+#             */
/*   Updated: 2019/04/12 17:24:40 by fnussbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include <time.h>

# define MAGIC_SIZE	4
# define NAME_SIZE	128
# define PAD_SIZE	4
# define BOT_SIZE	4
# define COMMENT_SIZE	2048

typedef struct	s_process
{
	char				regs[REG_NUMBER][REG_SIZE];
	void				*pc;
	char				carry;
	struct s_process	*next;
}				t_process;

typedef struct	s_time
{
	clock_t		begin;
	clock_t		current;
	clock_t		pause;
}				t_time;

typedef struct	s_player
{
	t_process	*process;
	char		*code;
	t_header	*header;
	char		*file_path;
	int			player_number;
	int			order_arg;
}				t_player;

typedef	struct	s_case {
	int			id;
	char		by;
}				t_case;

typedef struct	s_vm {
	t_player	*players[MAX_PLAYERS];
	t_case		arena[MEM_SIZE];
	int			cycles;
	int			players_alive;
	int			cycle_to_die;
	int			nb_process;
	int			stop;
	int			cycle_sec;
	int			number_of_live;
	int			last_player_live;
	int			dump_cycle;
}				t_vm;

void			refresh_window(t_vm *vm);
void			initialize_window(t_vm *vm);
void			close_window();

void			initialize_vm(t_vm *vm);

int				ft_parse_args(t_vm *vm, int ac, char **av);
void			ft_error_read(char *str);
void			ft_error_too_many();
void			ft_usage();

void			ft_print_players(t_vm *vm);

void			vm_read_byte(t_player *player, t_vm *vm);

#endif
