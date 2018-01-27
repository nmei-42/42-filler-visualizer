/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:55:50 by nmei              #+#    #+#             */
/*   Updated: 2018/01/25 18:43:03 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <libft.h>
#include "filler_viz.h"
#define IS_P1(x) ((x)=='O'||(x)=='o')
#define IS_P2(y) ((y)=='X'||(y)=='x')

/*
**	The vm header is 9 lines long
**	line 5 contains the p1 filler (ex: "launched ./players/player1.filler")
**	line 7 contains the p2 filler
**	If we just take everything after the '/' we'll have the filler name!
*/

int			read_header(t_game *game, int fd, ssize_t *ret, char *line)
{
	size_t	i;
	char	*pname;

	i = -1;
	while (++i < 9 && ((*ret = ft_get_next_line(fd, &line)) == 1))
	{
		if (i == 5 || i == 7)
		{
			if ((pname = ft_strrchr(line, '/')) != NULL)
			{
				pname++;
				if (i == 5)
					game->p1 = ft_strsub(pname, 0, ft_strlen(pname) - 7);
				else
					game->p2 = ft_strsub(pname, 0, ft_strlen(pname) - 7);
			}
			else
				disp_info(1);
		}
		free(line);
	}
	if (*ret > 0)
		return (0);
	else
		return (1);
}

/*
**	read_board()
**	1) If the line obtained in the read_turn() function was "Plateau " (8 chars)
**	   then it will be followed by two numbers separated by a ' ' describing
**	   the height and width of the game board. Easily obtained with ft_atoi
**	   and ft_strchr.
**	2) We then add a new link in our game state linked list
**	3) We then copy the current board state into our current game state
*/

void		read_board(t_game *game, int fd, ssize_t *ret, char *line)
{
	int	i;

	game->h = ft_atoi(line + 8);
	game->w = ft_atoi(ft_strchr(line + 8, ' '));
	free(line);
	gs_lstadd(&(game->gss), gs_lstnew(game, 0));
	if (game->first == NULL)
		game->first = game->gss;
	if (game->color_t_rt == NULL)
	{
		game->color_t_rt = (short *)malloc((game->h * game->w) * sizeof(short));
		ft_bzero(game->color_t_rt, (game->h * game->w) * sizeof(short));
	}
	game->gss->turn = game->turn_rt++;
	i = -1;
	while (i++ < game->h && (*ret = ft_get_next_line(fd, &line)) == 1)
	{
		if (i != 0)
			game->gss->board[i - 1] = board_strdup(game, (i - 1), line + 4);
		free(line);
	}
	ft_memcpy(game->gss->color_tab, game->color_t_rt,
		(game->h * game->w) * sizeof(short));
}

/*
**	read_next_piece()
**	1) If the line obtained in read_turn() was "Piece " (6 chars)
**	2) We first need to check if a player has already "placed" a piece on our
**	   current turn. If so that means the player gave a bad coordinate.
**	   We need to undo their point then add a new game state list element so
**	   that we can keep track of what the *other* player gets as a piece.
**	   Note: The new game state element if the players are 'turn switched'
**	         will not contain a copy of the game board.
**	3) We then read the piece height and width into our current game state
**	4) Then we copy the current piece into our current game state
*/

void		read_next_piece(t_game *game, int fd, ssize_t *ret, char *line)
{
	int		i;
	t_gslst *gss;

	gss = game->gss;
	if (gss->flags & PLACED)
	{
		(gss->flags & P1_PLACED) ? (game->p1_rt)-- : (game->p2_rt)--;
		gs_lstadd(&(game->gss), gs_lstnew(game, 1));
		gss = game->gss;
	}
	gss->piece_h = ft_atoi(line + 6);
	gss->piece_w = ft_atoi(ft_strchr(line + 6, ' '));
	free(line);
	gss->piece = (char **)malloc((gss->piece_h + 1) * sizeof(char *));
	i = 0;
	while (i < gss->piece_h && (*ret = ft_get_next_line(fd, &line)) == 1)
	{
		gss->piece[i++] = ft_strdup(line);
		free(line);
	}
}

/*
**	read_turn()
**	We'll get 1 line (after reading in the header)
**	1) If it contains "fin" we've finished!
**	2) If it contains "Plateau" we're about to get a board
**	3) If it contains "Piece" we're about to get a piece
**	   a) After the piece there will be one line describing which player
**		  is placing the piece and where they want to place it.
**	   IMPORTANT NOTE: We need to re-assign gss = game->gss because if
**	   there was a turn switch then the gane->gss will be pointing at the
**	   previous game state and not the most current state.
*/

int			read_turn(t_game *game, int fd, ssize_t *ret, char *line)
{
	t_gslst *gss;

	gss = game->gss;
	*ret = ft_get_next_line(fd, &line);
	if (ft_strstr(line, "fin"))
	{
		(gss->flags & P1_PLACED) ? (game->p1_rt)-- : (game->p2_rt)--;
		free(line);
		return (1);
	}
	else if (ft_strstr(line, "Plateau "))
		read_board(game, fd, ret, line);
	else if (ft_strstr(line, "Piece "))
	{
		read_next_piece(game, fd, ret, line);
		gss = game->gss;
		*ret = ft_get_next_line(fd, &line);
		gss->flags |= (ft_strchr(line, 'O')) ? P1_PLACED : 0;
		(gss->flags & P1_PLACED) ? (game->p1_rt)++ : (game->p2_rt)++;
		gss->piece_y = ft_atoi(line + 11);
		gss->piece_x = ft_atoi(ft_strchr(line + 11, ' '));
		gss->flags |= PLACED;
		free(line);
	}
	return (0);
}

/*
**	test()
**	Useful test function to make sure maps are being read in correctly
**	Run `test(game);` after reading vm output to get lots of useful information
*/

/*
**#include <stdio.h>
**
**void	test(t_game *game)
**{
**	t_gslst	*curr_state;
**	int		i;
**
**	printf("%s vs. %s\n", game->p1, game->p2);
**	curr_state = game->first;
**	while (curr_state)
**	{
**		if ((curr_state->flags & TURN_SWITCH) == 0)
**		{
**			printf("Turn: %d\n", curr_state->turn);
**			i = 0;
**			while (i < game->h)
**			{
**				printf("board: |%s| %d\n", curr_state->board[i], i);
**				i++;
**			}
**		}
**		i = 0;
**		printf("placer: %s\n",
**					(curr_state->flags & P1_PLACED) ? "P1" : "P2");
**		printf("pw: %d, ph: %d, px: %d, py: %d\n",
**			curr_state->piece_w, curr_state->piece_h,
**			curr_state->piece_x, curr_state->piece_y);
**		while (i < curr_state->piece_h)
**		{
**			printf("piece: |%s| %d\n", curr_state->piece[i], i);
**			i++;
**		}
**		printf("flags: %d\n", curr_state->flags);
**		printf("p1: %d, p2: %d\n", curr_state->p1_pts, curr_state->p2_pts);
**		curr_state = curr_state->next;
**	}
**	printf("total turns: %d\n", game->turn_rt);
**}
*/

/*
**	read_game()
**	Driving function to read a game that is output by the filler VM
*/

int			read_game(t_game *game, int fd, int argc, char *fpath)
{
	ssize_t	ret;
	char	*line;

	line = NULL;
	if ((fd = (argc == 1) ? 0 : open(fpath, O_RDONLY)) != -1)
	{
		if (read_header(game, fd, &ret, line) == 1)
			disp_info(0);
		while (1)
		{
			if (read_turn(game, fd, &ret, line) == 1)
				break ;
		}
		close(fd);
		return (0);
	}
	else
		return (1);
}
