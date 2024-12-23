/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flappybird.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:22:51 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/23 19:11:04 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/flap.h"

void	restart_game(t_data *data, t_move *move)
{
	int	i;

	data->score = 0;
	data->bird->y = (int)floor(WINDOW_HEIGHT / 2);

	move->bird_velocity = 0.0f;
	move->bird_y = data->bird->y;
	i = 0;
	while (i < move->n_pipes)
	{
		move->pipe_pos_x[i] = (move->spawn_pipe + move->pipe_gap_x) * (i + 1) + WINDOW_WIDTH;
		if (i == 0)
			move->pipe_pos_y[i] = (int)floor(WINDOW_HEIGHT / 2);
		else
			move->pipe_pos_y[i] = calc_pipe_y(data, move);
		move->pipe_score[i] = 0;
		i++;
	}

	data->gameover = 0;
}

void	check_score(t_data *data, t_move *move)
{
	int	i;

	i = 0;
	while (i < move->n_pipes)
	{
		if (move->pipe_pos_x[i] <= data->bird->x)
		{
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

void	calc_hitboxes(t_data *data, t_move *move)
{
	int	i;

	i = 0;
	while (i < move->n_pipes)
	{
		if (move->pipe_pos_x[i] <= data->bird->x + data->bird->width - 15
				&& data->bird->x + 30 <= move->pipe_pos_x[i] + data->pipe_top->width)
		{
			if (data->bird->y + 5 < move->pipe_pos_y[i] - move->pipe_gap_y / 2
					|| data->bird->y + data->bird->height - 5 > move->pipe_pos_y[i] + move->pipe_gap_y / 2)
				data->gameover = true;
		}
		i++;
	}
	if (move->bird_y >= WINDOW_HEIGHT - data->bird->height)
		data->gameover = true;
	if (data->gameover)
		add_player_score(data);
}

int		calc_pipe_y(t_data *data, t_move *move)
{
	float	pos;
	float	offset = 0.3;
	int		top = WINDOW_HEIGHT * offset;
	int		bot = WINDOW_HEIGHT * (1 - offset);

	srand(time(NULL));
	pos = (rand() % (bot - top + 1) + top);
	//pos = WINDOW_HEIGHT / 2;

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
	else if (keycode == 65293)
		restart_game(data, data->move);
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

	data->bird->y = (int)floor(move->bird_y);
}

int	check_frame(t_data *data)
{
	unsigned long			time;
	static unsigned long	last_time = 0;
	static unsigned long	last_time_sec = 0;
	static unsigned long	last_time_flap = 0;
	static unsigned long	fps = 0;
	static int				fps2;

	time = get_timediff((unsigned long)data->time);
	if (time - last_time >= 16666)
	{
		if (time - last_time_sec >= 1000000)
		{
			last_time_sec = time;
			fps2 = data->frame - fps;
			fps = data->frame;
		}
		
		data->frame++;
		last_time = time;
		
		if (!data->gameover)
		{
			update_bird(data, data->move);
			update_pipes(data, data->move);
			check_score(data, data->move);
			calc_hitboxes(data, data->move);
			draw_canvas(data);
		}
		else
		{
			draw_canvas(data);
			draw_gameover(data);
		}
		draw_fps(data, fps2);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit_msg(ft_strdup("gayass\n"));
	init_mlx(&data, av[1]);
	check_file(&data, "settings/settings.flap");
	init_imgs(&data);
	init_move(&data, data.move);
	data.hiscore = make_list(data.file_hiscore);

	draw_canvas(&data);
	data.time = get_time();
	mlx_hook(data.win, 2, 1L<<0, bird_flap, &data);
	mlx_hook(data.win, 17, 0, exit_flap_loop, &data);
	mlx_loop_hook(data.mlx, check_frame, &data);
	mlx_loop(data.mlx);
}
