/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:23:16 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/23 21:31:04 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAP_H
# define FLAP_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <time.h>
# include <math.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "data.h"

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 720
# endif
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1280
# endif

// init
void	init_mlx(t_data *data, char *player_name);
void	init_imgs(t_data *data);
void	init_move(t_data *data, t_move *move);

// read file
void	check_file(t_data *data, char *path);

// hiscore
t_hiscore	*make_list(char **arr);
t_hiscore	*get_head(t_hiscore *hiscore);
void		free_char_arr(char **bruh);
void		add_player_score(t_data *data);
void		free_hiscore(t_hiscore *hiscore);
void		write_hiscore(t_data *data);

// input
int		update_input(t_data *data, char c);
void	remove_input(t_data *data, int size);
void	draw_typingscreen(t_data *data);
int		bird_flap(int keycode, t_data *data);

//	draw
void	draw_canvas(t_data *data);
void	draw_fps(t_data *data, int fps);
void	draw_gameover(t_data *data);

int		draw_sentence(t_data *data, char *str, int x, int y, int size);
int		draw_square(t_data *data, int x, int y, int size);
int		draw_face(t_data *data, int x, int y, int size, int face);
int		draw_line_hor(t_data *data, int x, int y, int size);
int		draw_line_vert(t_data *data, int x, int y, int size);
int		get_string_width(t_data *data, char *str, int size);

// time & frame & loop?
unsigned long	get_time();
unsigned long	get_timediff(unsigned long start);
int				bird_flap(int keycode, t_data *data);
int				calc_pipe_y(t_data *data, t_move *move);
void			restart_game(t_data *data, t_move *move);

// error and exit
void	exit_msg(char *msg);
void	add_error(t_data *data, char *msg);
void	exit_flap(t_data *data, char *msg, bool init);
int		exit_flap_loop(t_data *data);
#endif
