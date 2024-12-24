/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 05:23:35 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/23 20:37:26 by sklaps           ###   ########.fr       */
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
	float	pipe_velocity;
	int		pipe_gap_x;
	int		pipe_gap_y;
	int		*pipe_pos_x;
	int		*pipe_pos_y;
	int		*pipe_score;
	int		spawn_pipe;
	int		n_pipes;
}	t_move;

typedef struct	s_hiscore
{
	char				*name;
	int					score;
	struct s_hiscore	*next;
	struct s_hiscore	*prev;
}	t_hiscore;

typedef struct	s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					tcolor;
	bool				tcolorbool;
	bool				giving_input;
	struct s_img		*bg;
	struct s_img		*pipe_top;
	struct s_img		*pipe_bot;
	struct s_img		*bird;
	struct s_move		*move;
	char				*player_name;
	bool				error;
	char				*errstr;
	char				**file;
	char				**letters;
	char				**file_hiscore;
	char				*hiscore_path;
	struct s_hiscore	*hiscore;
	bool				letter_calc;
	unsigned long		time;
	unsigned long		frame;
	int					gameover;
	unsigned long		score;
}	t_data;

#endif
