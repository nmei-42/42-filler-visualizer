/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:15:54 by nmei              #+#    #+#             */
/*   Updated: 2018/01/23 00:33:48 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_viz.h"

/*
**	color_lint - generates an intermediate color between c1 and c2.
**
**	Colors are stored in the following hex format:
**	0 x |  F F  |   F F   |  F F  |
**	    |  red  |  green  | blue  |
**
**	So what we can do is mask and isolate each color channel using bit shifting
**	and perform linear interpolation on each channel before recombining.
**
**	Each channel is 8 bits (0 to 255).
*/

int			color_lint(int c1, int c2, double decimal_percent)
{
	int	r;
	int	g;
	int	b;

	if (c1 == c2)
		return (c1);
	if (decimal_percent == 0.0)
		return (c1);
	if (decimal_percent == 1.0)
		return (c2);
	r = (int)ft_lint(((c1 >> 16) & 0xFF), ((c2 >> 16) & 0xFF), decimal_percent);
	g = (int)ft_lint(((c1 >> 8) & 0xFF), ((c2 >> 8) & 0xFF), decimal_percent);
	b = (int)ft_lint((c1 & 0xFF), (c2 & 0xFF), decimal_percent);
	return (r << 16 | g << 8 | b);
}

int			choose_board_color(t_envars *e, int row, int col)
{
	t_game	*g;
	t_gslst	*gs;
	double	progress;
	int		color;

	gs = e->curr_gs;
	g = e->g;
	color = 0;
	progress = (double)gs->color_tab[idx(row, col, g->w)] / (double)g->turn_rt;
	if (gs->board[row][col] == '.')
		color = 0xD3D3D3;
	else if (gs->board[row][col] == 'O')
		color = color_lint(0xFFC4C4, 0xFF0000, progress);
	else if (gs->board[row][col] == 'o')
		color = 0xFFA500;
	else if (gs->board[row][col] == 'X')
		color = color_lint(0xC4C4FF, 0x0000FF, progress);
	else if (gs->board[row][col] == 'x')
		color = 0x00A5FF;
	return (color);
}

int			choose_piece_color(t_envars *e, int row, int col)
{
	int		color;
	t_gslst	*gs;

	gs = e->curr_gs;
	color = 0;
	if (gs->piece[row][col] == '.')
		color = 0xD3D3D3;
	else if (gs->piece[row][col] == '*')
	{
		if (gs->flags & P1_PLACED)
			color = 0xFFA500;
		else
			color = 0x00A5FF;
	}
	return (color);
}
