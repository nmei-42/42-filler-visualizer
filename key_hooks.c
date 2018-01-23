/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:28:08 by nmei              #+#    #+#             */
/*   Updated: 2018/01/23 12:12:19 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
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

/*
**	keydown_hook - similar to key_pressed_hook but will only be called when
**	a key has been pressed AND released.
**
**	The following key are mapped:
**	'esc' (53) = quit the program
**	'p' (35) = PsYcHeDeLiC MoDe!!
**	'c'	(8) = toggle color modes
**	's' (1) = color surprise!
**	'd' (2) = psychedelic surprise!
**	'l'	(37) = linear continous color mode
**	'f' (3) = Stop mouse cursor tracking for interactive fractals
**	'r' (15) = reset the fractal back to original window size, iter limits, and
**	color palette
*/

int			keydown_hook(int key, t_envars *env)
{
	if (key == 53)
	{
		cleanup_env(env);
		exit(0);
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
	if (!(key == 53 || key == 15))
		render(e);
	return (0);
}
