/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:27:16 by nmei              #+#    #+#             */
/*   Updated: 2018/01/23 00:33:30 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "filler_viz.h"

/*
**	idx() - Useful function to get the row, col value from a flattened
**	2D matrix. Dim the is the 'width' of the matrix...
*/

int			idx(int row, int col, int dim)
{
	return (row * dim + col);
}

/*
**	ft_lint - Linear INTerpolation between two points given a decimal percent
**
**	We don't do: (start + decimal_percent * (end - start)) because if
**	start and end differ significantly in magnitude then we lose precision.
**
**	Test with: ft_lint(-16.0e30, 16.0, 1.0)
*/

double		ft_lint(double start, double end, double decimal_percent)
{
	if (start == end)
		return (start);
	return (start * (1.0 - decimal_percent) + (end * decimal_percent));
}

/*
**	board_strdup()
**	Custom version of ft_strdup() just for this visualizer
**	On top of duplicating a string, it also looks for 'o' and 'x' chars
**	in the current map and assigns the current running turn total to the
**	game color table;
*/

char		*board_strdup(t_game *game, int i, const char *s)
{
	char	*new_s;
	char	*start;
	size_t	len;
	size_t	j;

	len = ft_strlen(s);
	if ((new_s = (char *)malloc((len + 1) * sizeof(*new_s))) != NULL)
	{
		new_s[len] = '\0';
		start = new_s;
		j = 0;
		while (j < len)
		{
			*new_s = *s;
			if (*s == 'o' || *s == 'x')
				game->color_t_rt[idx(i, (int)j, game->w)] = game->gss->turn;
			new_s++;
			s++;
			j++;
		}
		return (start);
	}
	return (NULL);
}
