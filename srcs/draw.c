/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 07:38:55 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/21 17:50:51 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/flap.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (data->tcolorbool && color == data->tcolor)
		return ;
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_img_on_canvas(t_data *data, t_img *img, int x, int y)
{
	int	i;
	int	j;
	int	color;
	int	pos;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			pos = (i * img->line_length + j * (img->bits_per_pixel / 8));
			color = *(int *)(img->tex_data + pos);
			my_pixel_put(data, j + x, i + y, color);
			j++;
		}
		i++;
	}
}

void	draw_canvas(t_data *data)
{
	int	i = data->bg->height;
	int	j;
	int pos_y;

	draw_img_on_canvas(data, data->bg, 0, 0);
	if (data->bg->height < WINDOW_HEIGHT)
	{
		while (i < WINDOW_HEIGHT)
		{
			j = 0;
			while (j < WINDOW_WIDTH)
				my_pixel_put(data, j++, i, 0x808080);
			i++;
		}
	}

	i = 0;
	while (i < data->move->n_pipes)
	{
		pos_y = data->move->pipe_pos_y[i] - ((data->move->pipe_gap_y / 2) + data->pipe_top->height);
		draw_img_on_canvas(data, data->pipe_top, data->move->pipe_pos_x[i], pos_y);
		pos_y = data->move->pipe_pos_y[i] + (data->move->pipe_gap_y / 2);
		draw_img_on_canvas(data, data->pipe_bot, data->move->pipe_pos_x[i], pos_y);
		i++;
	}
	draw_img_on_canvas(data, data->bird, data->bird->x, data->bird->y);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
