/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:47:52 by nmei              #+#    #+#             */
/*   Updated: 2018/01/29 11:28:19 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "filler_viz.h"

/*
** All sound samples were acquired from:
** https://freesound.org/people/shawshank73/sounds/119172/
*/

int		play_sound(char *command)
{
	int		status;

	status = 0;
	status = system(command);
	return (status);
}

void	choose_sound(t_envars *e, t_gslst *gs)
{
	if (e->prev_turn != gs->turn)
	{
		if (gs->turn == 0 && (gs->flags & TURN_SWITCH) == 0)
			play_sound("afplay ./sounds/death_match.mp3 &");
		if (gs->flags & TURN_SWITCH)
			play_sound("afplay ./sounds/finish_him.mp3 &");
		if (gs->turn == e->g->turn_rt - 1)
		{
			if (e->g->p1_rt == e->g->p2_rt)
				play_sound("afplay ./sounds/its_a_tie.mp3 &");
			else if (e->g->p1_rt > e->g->p2_rt)
				play_sound("afplay ./sounds/player_one_you_win.mp3 &");
			else if (e->g->p2_rt > e->g->p1_rt)
				play_sound("afplay ./sounds/player_two_you_win.mp3 &");
		}
		e->prev_turn = gs->turn;
	}
}
