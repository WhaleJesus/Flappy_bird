/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 07:38:55 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/20 09:31:30 by sklaps           ###   ########.fr       */
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
