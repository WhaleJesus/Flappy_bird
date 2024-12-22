/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:23:16 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/22 08:05:41 by sklaps           ###   ########.fr       */
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
#  define WINDOW_WIDTH 720
# endif

// init
void	init_mlx(t_data *data);
void	init_imgs(t_data *data);
void	init_move(t_data *data, t_move *move);

// read file
void	check_file(t_data *data, char *path);

//	draw
void	draw_canvas(t_data *data);
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

// error and exit
void	exit_msg(char *msg);
void	add_error(t_data *data, char *msg);
void	exit_flap(t_data *data, char *msg, bool init);
int		exit_flap_loop(t_data *data);
#endif
