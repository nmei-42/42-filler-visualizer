/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:28:08 by nmei              #+#    #+#             */
/*   Updated: 2018/01/26 17:03:03 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <libft.h>
#include "filler_viz.h"

static void	cleanup_env(t_envars *env)
{
	mlx_destroy_image(env->mlx, (&env->image)->image);
	mlx_destroy_window(env->mlx, env->win);
}

void		reset_env(t_envars *env)
{
	env->curr_gs = env->g->first;
	render(env);
}

void		print_current_gs(t_envars *env)
{
	int i;
	int p;

	p = ((env->curr_gs->flags & P1_PLACED)) ? 1 : 2;
	if (p == 1)
		ft_printf("\n$$$ exec p%d : [./%s.filler]\n", p, env->g->p1);
	else if (p == 2)
		ft_printf("\n$$$ exec p%d : [./%s.filler]\n", p, env->g->p2);
	ft_printf("Plateau %d %d:\n", env->g->h, env->g->w);
	ft_printf("    ");
	i = -1;
	while (++i < env->g->w)
		ft_printf("%d", i % 10);
	ft_printf("\n");
	i = -1;
	while (++i < env->g->h)
		ft_printf("%03d %s\n", i, env->curr_gs->board[i]);
	ft_printf("Piece %d %d:\n", env->curr_gs->piece_h, env->curr_gs->piece_w);
	i = -1;
	while (++i < env->curr_gs->piece_h)
		ft_printf("%s\n", env->curr_gs->piece[i]);
	ft_printf("\n");
}

/*
**	keydown_hook - similar to key_pressed_hook but will only be called when
**	a key has been pressed AND released.
**
**	The following key are mapped:
**	'esc' (53) = quit the program
**	'p' (35) = printf the player, board, and piece for current game turn
**	'r' (15) = reset the game back to turn 0
*/

int			keydown_hook(int key, t_envars *env)
{
	if (key == 53)
	{
		cleanup_env(env);
		exit(0);
	}
	if (key == 35)
	{
		print_current_gs(env);
	}
	if (key == 15)
		reset_env(env);
	return (0);
}

/*
**	key_pressed_hook - while any of the arrow keys on the keyboard are
**	held down, shift the map in that direction.
**
**	← (123) = move back one turn
**	→ (124) = move forward one turn
**	↓ (125) = move forward 9x
**	↑ (126) = move backward 9x
*/

int			key_pressed_hook(int key, t_envars *e)
{
	int i;

	i = -1;
	if (key == 124)
		e->curr_gs = (e->curr_gs->next) ? e->curr_gs->next : e->curr_gs;
	if (key == 123)
		e->curr_gs = (e->curr_gs->prev) ? e->curr_gs->prev : e->curr_gs;
	if (key == 125)
		while (++i < 9)
			e->curr_gs = (e->curr_gs->next) ? e->curr_gs->next : e->curr_gs;
	if (key == 126)
		while (++i < 9)
			e->curr_gs = (e->curr_gs->prev) ? e->curr_gs->prev : e->curr_gs;
	if (!(key == 53 || key == 15 || key == 35))
		render(e);
	return (0);
}
