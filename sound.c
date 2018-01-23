/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:47:52 by nmei              #+#    #+#             */
/*   Updated: 2018/01/23 12:15:40 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "filler_viz.h"

#include <stdio.h>

/*
** All sound samples were acquired from:
** https://freesound.org/people/shawshank73/sounds/119172/
*/

int		play_sound(char *fpath)
{
	char	*command;
	int		cmd_len;
	int		status;

	command = NULL;
	status = 0;
	cmd_len = ft_strlen("afplay ") + ft_strlen(fpath);
	if ((command = (char *)malloc(cmd_len + 1)) != NULL)
	{
		command = ft_strcat(ft_strcat(command, "afplay "), fpath);
		command = ft_strcat(command, "\0");
		status = system(command);
		free(command);
	}
	return (status);
}

void	choose_sound(t_envars *e, t_gslst *gs)
{
	static int played = 1;

	if (played == 1)
	{
		if (gs->turn == 0 && (gs->flags & TURN_SWITCH) == 0)
			played = play_sound("./sounds/death_match.mp3 &");
		if (gs->flags & TURN_SWITCH)
			played = play_sound("./sounds/finish_him.mp3 &");
		if (gs->turn == e->g->turn_rt - 1)
		{
			if (e->g->p1_rt > e->g->p2_rt)
				played = play_sound("./sounds/player_one_you_win.mp3 &");
			else if (e->g->p2_rt > e->g->p1_rt)
				played = play_sound("./sounds/player_two_you_win.mp3 &");
			else
				played = play_sound("./sounds/its_a_tie.mp3 &");
		}
	}
	else
	{
		played = 1;
	}
}
