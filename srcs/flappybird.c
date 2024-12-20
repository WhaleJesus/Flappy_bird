/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flappybird.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:22:51 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/20 09:49:36 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/flap.h"

void	draw_pipes(t_data *data, t_move *move)
{
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

void	check_frame(t_data *data)
{
	unsigned long			time;
	static unsigned long	last_time = 0;
	static unsigned long	last_time_sec = 0;
	static unsigned long	last_time_flap = 0;

	time = get_timediff((unsigned long)data->time);
/*
	if (data->move->flap == 1)
	{
		last_time_flap = time;
		data->move->flap = 2;
	}
	if (data->move->flap == 2 && time - last_time_flap >= 2 * 1000000)
		data->move->flap = 0;
*/
	if (time - last_time >= 16666)
	{
		if (time - last_time_sec >= 1000000)
		{
			last_time_sec = time;
			printf("fps: %lu bird_y: %f\n", data->frame % 60, data->move->bird_y);
		}
		data->frame++;
		last_time = time;
		
		update_bird(data, data->move);
		draw_canvas(data);
	}
}

int	flap_loop(t_data *data)
{
	check_frame(data);
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
	mlx_loop_hook(data.mlx, flap_loop, &data);
	mlx_loop(data.mlx);
}
