/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 05:23:35 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/20 09:35:23 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct	timeval t_timeval;

typedef struct	s_img
{
	int		height;
	int		width;
	int		x;
	int		y;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*tex_data;
	char	*path;
}	t_img;

typedef struct	s_move
{
	float	delta_time;
	float	bird_y;
	float	bird_velocity;
	int		gravity;
	int		flap_strength;
	int		flap;
	float 	pipe_x;
	int		pipe_gap_x;
	int		pipe_gap_y;
	int		*pipe_pos;
}	t_move;

typedef struct	s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				tcolor;
	bool			tcolorbool;
	struct s_img	*bg;
	struct s_img	*pipe_top;
	struct s_img	*pipe_bot;
	struct s_img	*bird;
	struct s_move	*move;
	bool			error;
	char			*errstr;
	char			**file;
	unsigned long	time;
	unsigned long	frame;
	int				gameover;
}	t_data;

#endif
