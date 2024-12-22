/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 07:38:55 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/22 19:06:03 by sklaps           ###   ########.fr       */
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

int	draw_face(t_data *data, int x, int y, int size, int face)
{
	int		i;
	int		j;
	int		iStart;
	int		jStart;
	int		iStop;
	int		jStop;
	float	offset;

	offset = 0.3;
	// up
	if (face == 0)
	{
		iStart = 0 - size * offset;
		jStart = 0 - size * offset;
		iStop = 0;
		jStop = size + (size * offset);
	}
	// right
	else if (face == 1)
	{
		iStart = 0 - size * offset;
		jStart = size;
		iStop = size + (size * offset);
		jStop = size + (size * offset);
	}
	//down
	else if (face == 2)
	{
		iStart = size;
		jStart = 0 - (size * offset);
		iStop = size + (size * offset);
		jStop = size + (size * offset);
	}
	// left
	else if (face == 3)
	{
		iStart = 0 - size * offset;
		jStart = 0 - size * offset;
		iStop = size + (size * offset);
		jStop = 0;
	}
	i = iStart;
	while (i < iStop)
	{
		j = jStart;
		while (j < jStop)
			my_pixel_put(data, x + j++, y + i, 0x010000);
		i++;
	}
}

int	draw_square(t_data *data, int x, int y, int size)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!data->letter_calc)
			{
				color = 0xfcba03;
				my_pixel_put(data, x + j++, y + i, color);
			}
		}
		i++;
	}
	return (j);
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

void	draw_gameover(t_data *data)
{
	int		i;
	int		j;
	float	offset;
	int		x;
	int		y;
	char	*str;
	char	*tmp;
	int		size;

	offset = 0.2;
	
	i = WINDOW_HEIGHT * offset;
	while (i < WINDOW_HEIGHT * (1 - offset))
	{
		j = WINDOW_WIDTH * offset;
		while (j < WINDOW_WIDTH * (1 - offset))
		{
			//my_pixel_put(data, j, i, 0x03fcfc);
			j++;
		}
		i++;
	}
	
	
	size = 15;
	str = "game over";
	x = (WINDOW_WIDTH / 2) - (get_string_width(data, str, size) / 2);
	y = WINDOW_HEIGHT * offset + size;
	draw_sentence(data, str, x, y, size);
	
	y += 6 * size;
	size = 10;
	tmp = ft_itoa(data->score);
	str = ft_strjoin("score: ", tmp);
	x = (WINDOW_WIDTH / 2) - (get_string_width(data, str, size) / 2);
	draw_sentence(data, str, x, y, size);
}

void	draw_score(t_data *data)
{
	int		x;
	int		y;
	int		size;
	char	*score;

	size = 25;
	score = ft_itoa(data->score);
	x = (WINDOW_WIDTH / 2) - (get_string_width(data, score, size) / 2);
	y = WINDOW_HEIGHT * 0.05;
	draw_sentence(data, score, x, y, size);
	free(score);
}

void	draw_fps(t_data *data, int fps)
{
	int		x;
	int		y;
	int		offset;
	int		size;
	char	*sfps;

	size = 10;
	offset = 5;
	sfps = ft_itoa(fps);
	x = offset;
	y = WINDOW_HEIGHT - offset - (size * 5);
	x = draw_sentence(data, sfps, x, y, size);
	free(sfps);
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

	if (!data->gameover)
		draw_score(data);

	draw_img_on_canvas(data, data->bird, data->bird->x, data->bird->y);
}
