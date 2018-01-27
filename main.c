/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:52:48 by nmei              #+#    #+#             */
/*   Updated: 2018/01/26 16:35:49 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "filler_viz.h"

void			disp_info(int mode)
{
	if (mode == 0)
	{
		write(2, "\nUsage: ./filler_viz [filler_vm_output] ", 40);
		write(2, "\nOR\nfiller_vm [vm_options] | ./filler_viz\n\n", 43);
		exit(1);
	}
	else if (mode == 1)
	{
		write(2, "An error occurred reading the file or input.", 44);
		write(2, " Is it valid?\n", 14);
		exit(1);
	}
	else if (mode == 2)
	{
		ft_printf("\n			Filler Viz 42!!\n\
		left arrow (←): move back one turn\n\
		right arrow (→): move forward one turn\n\
		down arrow (↓): move forward 9x\n\
		up arrow (↑): move backward 9x\n\
		p: Print the current player, board, and piece to console\n\
		r: Reset game back to turn 0\n\
		esc: Quit :(\n\n");
	}
}

void			setup_game(t_game *game)
{
	game->p1 = NULL;
	game->p2 = NULL;
	game->turn_rt = 0;
	game->h = 0;
	game->w = 0;
	game->p1_rt = 0;
	game->p2_rt = 0;
	game->color_t_rt = NULL;
	game->gss = NULL;
	game->first = NULL;
}

void			setup_env(t_envars *e)
{
	e->b_glen = 12;
	e->b_lpad = e->b_glen;
	e->b_tpad = 70;
	e->b_row_space = 1;
	e->b_col_space = 1;
	e->w = ((e->g->w + 1) * e->b_glen + e->b_lpad) * 2;
	e->h = (e->g->h + 1) * e->b_glen + e->b_tpad;
	e->size = e->w * e->h;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->w, e->h, "Filler Viz 42");
	init_img(e);
	mlx_key_hook(e->win, keydown_hook, e);
	mlx_hook(e->win, 2, 0, key_pressed_hook, e);
}

/*
**	main - function where we start our mlx session
**	There are additional hooks that can be found!
**	See: https://github.com/qst0/ft_libgfx
**	Of particular interest are the mouse press, release, and movement hooks
**	which are mapped to 4, 5, and 6 respectively.
*/

int				main(int argc, const char *argv[])
{
	t_envars	env;
	t_game		game;

	if (argc == 1 || argc == 2)
	{
		setup_game(&game);
		if (read_game(&game, env.fd, argc, (char *)argv[1]) == 0)
		{
			disp_info(2);
			env.g = &game;
			env.curr_gs = game.first;
			setup_env(&env);
			render(&env);
			mlx_loop(env.mlx);
			return (0);
		}
		else
			disp_info(1);
	}
	disp_info(0);
}
