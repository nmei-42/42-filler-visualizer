/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_viz.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmei <nmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:30:14 by nmei              #+#    #+#             */
/*   Updated: 2018/01/26 20:42:05 by nmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VIZ_H
# define FILLER_VIZ_H
# include <stddef.h>
# define TURN_SWITCH	1
# define PLACED			2
# define P1_PLACED		4

/*
**	t_gslst - 'game state list'
**	Contains:
**
**	- The current piece width
**	- The current piece height
**	- The x position where the player wants to place the piece
**	- The y position where the player wants to place the piece
**
**	- flag variable:
**
**	TURN_SWITCH: indicating if a player messed up in the previous state
**	P1_PLACED: indicating if p1 placed the piece (otherwise p2 placed it)
**	PLACED: whether a piece has already been placed in the current state
**
**	- Current turn count
**	- Number of points that p1 has in the current state
**	- Number of points that p2 has in the current state
**	- Board double pointer to store a board state
**	- Piece double pointer to store a piece
**	- Pointer to the previous game state
**	- Pointer to the next game state
*/

typedef struct		s_gslst
{
	short			piece_w;
	short			piece_h;
	short			piece_x;
	short			piece_y;
	short			flags;
	int				turn;
	int				p1_pts;
	int				p2_pts;
	char			**board;
	short			*color_tab;
	char			**piece;
	struct s_gslst	*prev;
	struct s_gslst	*next;
}					t_gslst;

/*
**	t_game
**	Contains:
**
**	- Player 1 name
**	- Player 2 name
**	- Running total of turns in the game
**	- Height of the game board
**	- width of the game board
**	- Running Total of player 1's points
**	- Running Total of player 2's points
**	- A pointer to our game states list
**	- A pointer to the very first element of the game states list
*/

typedef struct		s_game
{
	char			*p1;
	char			*p2;
	int				turn_rt;
	int				h;
	int				w;
	int				p1_rt;
	int				p2_rt;
	short			*color_t_rt;
	t_gslst			*gss;
	t_gslst			*first;
}					t_game;

/*
**	t_image
**	struct to contain variables relevant to mlx images
*/

typedef struct		s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				line_s;
	int				endian;
}					t_image;

typedef struct		s_envars
{
	void			*mlx;
	void			*win;
	int				w;
	int				h;
	int				size;
	int				fd;
	int				p1_l;
	int				p2_l;
	int				b_glen;
	int				b_lpad;
	int				b_tpad;
	int				b_row_space;
	int				b_col_space;
	int				prev_turn;
	t_game			*g;
	t_gslst			*curr_gs;
	t_image			image;
}					t_envars;

/*
**	general_utils.c
*/
int					idx(int row, int col, int dim);
double				ft_lint(double start, double end, double decimal_percent);
char				*board_strdup(t_game *game, int i, const char *s);

/*
**	color.c
*/
int					choose_board_color(t_envars *e, int row, int col);
int					choose_piece_color(t_envars *e, int row, int col);

/*
**	main.c
*/
void				disp_info(int mode);
void				setup_env(t_envars *env);

/*
**	image.c
*/
int					idx(int row, int col, int dim);
void				init_img(t_envars *env);
void				img_pixel_put(t_envars *env, double x, double y, int color);
void				clear_img(t_envars *env);

/*
**	key_hooks.c
*/
int					keydown_hook(int key, t_envars *env);
int					key_pressed_hook(int key, t_envars *env);

/*
**	game_state_list_utils.c
*/
t_gslst				*gs_lstnew(t_game *game, int turn_switch);
void				gs_lstadd(t_gslst **gsts, t_gslst *new);

/*
**	read_utils.c
*/
int					read_game(t_game *game, int fd, int argc, char *fpath);

/*
**	render_str.c
*/
void				render_scoreboard(t_envars *e, t_gslst *gs);
void				render_piece_pos(t_envars *e, t_gslst *gs);

/*
**	render.c
*/
void				render(t_envars *env);

/*
**	sound.c
*/
int					play_sound(char *fpath);
void				choose_sound(t_envars *e, t_gslst *gs);

#endif
