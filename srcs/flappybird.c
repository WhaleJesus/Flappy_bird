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

void	init_img(t_data *data, t_img *img, char *path)
{
	void	*texture;

	texture = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	img->img = texture;
	img->tex_data = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_mlx(&data);
}
