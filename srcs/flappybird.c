/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flappybird.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:22:51 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/21 21:34:44 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/flap.h"

void	calc_hitboxes(t_data *data, t_move *move)
{
	int	i;

	i = 0;
	while (i < move->n_pipes)
	{
		if (move->pipe_pos_x[i] <= data->bird->x + data->bird->width
				&& data->bird->x <= move->pipe_pos_x[i] + data->pipe_top->width)
		{
			if (data->bird->y < move->pipe_pos_y[i] - move->pipe_gap_y / 2
					|| data->bird->y + data->bird->height > move->pipe_pos_y[i] + move->pipe_gap_y / 2)
			{
				printf("hit\n");
				data->gameover = true;
			}
			if (move->pipe_score[i] == 0)
			{
				data->score++;
				move->pipe_score[i] = 1;
				printf("Score: %lu\n", data->score);
			}
		}
		i++;
	}
}

int		calc_pipe_y(t_data *data, t_move *move)
{
	float	pos;

	pos = WINDOW_HEIGHT / 2;

	return ((int)floor(pos));
}

void	update_pipes(t_data *data, t_move *move)
{
	int		i;
	float	pos;

	i = 0;
	while (i < move->n_pipes)
	{
		pos = (float)move->pipe_pos_x[i];
		pos -= (move->pipe_velocity * move->delta_time);
		if (pos < data->pipe_top->width * -1)
		{
			pos = (float)move->spawn_pipe + WINDOW_WIDTH;
			move->pipe_pos_y[i] = calc_pipe_y(data, move);
			move->pipe_score[i] = 0;
		}
		move->pipe_pos_x[i] = (int)floor(pos);
		i++;
	}
}

int	bird_flap(int keycode, t_data *data)
{
	//printf("keycode: %i\n", keycode);
	if (keycode == 32)
		data->move->flap = 1;
	else if (keycode == 65307)
		exit_flap_loop(data);
	return (0);
}

void	update_bird(t_data *data, t_move *move)
{
	if (move->flap == 0)
		move->bird_velocity += (move->gravity * move->delta_time);
	else
	{
		move->bird_velocity = move->flap_strength;
		move->flap = 0;
	}
	move->bird_y += (move->bird_velocity * move->delta_time);
	
	if (move->bird_y >= WINDOW_HEIGHT - data->bird->height)
		data->gameover = 1;

	data->bird->y = (int)floor(move->bird_y);
}

int	check_frame(t_data *data)
{
	unsigned long			time;
	static unsigned long	last_time = 0;
	static unsigned long	last_time_sec = 0;
	static unsigned long	last_time_flap = 0;
	static unsigned long	fps = 0;

	time = get_timediff((unsigned long)data->time);
	if (time - last_time >= 16666)
	{
		if (time - last_time_sec >= 1000000)
		{
			last_time_sec = time;
			printf("fps: %lu\n", data->frame - fps);
			fps = data->frame;
		}
		data->frame++;
		last_time = time;
		
		if (!data->gameover)
		{
			update_bird(data, data->move);
			update_pipes(data, data->move);
			calc_hitboxes(data, data->move);
			draw_canvas(data);
		}
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit_msg(ft_strdup("gayass\n"));
	init_mlx(&data);
	check_file(&data, av[1]);
	init_imgs(&data);
	init_move(&data, data.move);
	
	draw_canvas(&data);
	data.time = get_time();
	mlx_hook(data.win, 2, 1L<<0, bird_flap, &data);
	mlx_hook(data.win, 17, 0, exit_flap_loop, &data);
	mlx_loop_hook(data.mlx, check_frame, &data);
	mlx_loop(data.mlx);
}
