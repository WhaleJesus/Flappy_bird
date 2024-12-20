/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:23:16 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/20 05:35:46 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAP_H
# define FLAP_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
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
void	init_mlx(t_data *data);
void	init_imgs(t_data *data);
void	init_move(t_data *data, t_move *move);

// read file
void	check_file(t_data *data, char *path);

//	draw
void	draw_canvas(t_data *data);

// time & frame & loop?
unsigned long	get_time();
unsigned long	get_timediff(unsigned long start);
int				bird_flap(int keycode, t_data *data);

// error and exit
void	exit_msg(char *msg);
void	add_error(t_data *data, char *msg);
void	exit_flap(t_data *data, char *msg, bool init);
int		exit_flap_loop(t_data *data);
#endif
