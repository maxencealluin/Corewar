/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:39:59 by malluin           #+#    #+#             */
/*   Updated: 2019/04/17 19:21:08 by malluin          ###   ########.fr       */
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
	unsigned char		regs[REG_NUMBER][REG_SIZE];
	void				*pc;
	char				carry;
	int					wait_cycles;
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
	t_process	**process;
	char		*code;
	t_header	*header;
	void		*code_start;
	char		*file_path;
	int			player_number;
	int			order_arg;
	int			nb_process;
	char		alive;
}				t_player;

typedef	struct	s_case {
	int				id;
	unsigned char	by;
}				t_case;

typedef struct	s_vm {
	t_player	*players[MAX_PLAYERS];
	t_case		arena[MEM_SIZE];
	// char		play_order[MAX_PLAYERS];
	int			cycles;
	int			players_alive;
	int			cycle_to_die;
	int			nb_process;
	int			stop;
	int			cycle_sec;
	int			number_of_live;
	int			last_player_live;
	int			dump_cycle;
	int			nb_players;
	char		visualization;
	int			*order;
}				t_vm;

// NCURSES

void			refresh_window(t_vm *vm);
void			initialize_window(t_vm *vm);
void			close_window();
int				count_players(t_vm *vm);



// INTIALIZATION

void			initialize_vm(t_vm *vm);
void			add_player(t_vm *vm, char *path, int next_nb, int i);



// PARSING

int				ft_parse_args(t_vm *vm, int ac, char **av);
void			vm_read_byte(t_player *player, t_vm *vm);

// INIT + UTILS

void			create_processes(t_vm *vm);
int				read_reg(unsigned char *str);
void			assign_reg(t_process *process, short reg, int value);

// MAIN LOOP

void			main_loop(t_vm *vm);


// PRINT
void			print_intro(t_vm *vm);
void			dump_memory(t_vm *vm);

// ?? franck

void			pick_order(t_vm *vm, int *tab);
void			print_op();


// DEBUG

void			ft_print_players(t_vm *vm);
void			ft_print_xstr(int size, char *str, int wid);
void			ft_print_xarena(t_vm *vm, int wid);
void			increment_memory(t_vm *vm);

// ERRORS
void			ft_error_read(char *str);
void			error_read();
void			error_champ_to_big();
void			ft_error_too_many();
void			ft_usage();
void			ft_incorrect_number();

#endif
