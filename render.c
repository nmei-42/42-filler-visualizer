/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:05:17 by nmei              #+#    #+#             */
/*   Updated: 2018/01/23 00:32:43 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "filler_viz.h"

void	draw_rect(t_envars *env, int row, int col, int color)
{
	int	im_row;
	int	im_col;

	im_row = row + env->b_tpad + env->b_row_space - 1;
	while (++im_row < row + env->b_glen + env->b_tpad)
	{
		im_col = col + env->b_lpad + env->b_col_space - 1;
		while (++im_col < col + env->b_glen + env->b_lpad)
		{
			img_pixel_put(env, im_col, im_row, color);
		}
	}
}

void	render_board(t_envars *env, t_gslst *gs)
{
	int row;
	int col;
	int	color;

	row = -1;
	while (++row < env->g->h)
	{
		col = -1;
		while (++col < env->g->w)
		{
			if ((gs->flags & TURN_SWITCH) == 0)
			{
				color = choose_board_color(env, row, col);
				draw_rect(env, row * env->b_glen, col * env->b_glen, color);
			}
		}
	}
}

void	render_next_piece(t_envars *e, t_gslst *gs)
{
	int color;
	int row;
	int col;
	int	row_offsetted;
	int	col_offsetted;

	row = -1;
	while (++row < gs->piece_h)
	{
		col = -1;
		while (++col < gs->piece_w)
		{
			color = choose_piece_color(e, row, col);
			row_offsetted = row * e->b_glen;
			col_offsetted = col * e->b_glen + ((e->g->w + 1) * e->b_glen);
			draw_rect(e, row_offsetted, col_offsetted, color);
		}
	}
}

void	render(t_envars *env)
{
	t_gslst *gs;

	gs = env->curr_gs;
	clear_img(env);
	render_board(env, gs);
	render_next_piece(env, gs);
	mlx_put_image_to_window(env->mlx, env->win, env->image.image, 0, 0);
	render_scoreboard(env, gs);
	render_piece_pos(env, gs);
	choose_sound(env, gs);
}
