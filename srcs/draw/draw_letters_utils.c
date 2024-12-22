/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_letters_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 02:01:50 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/22 04:55:36 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/flap.h"

int	draw_line_vert(t_data *data, int x, int y, int size)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		draw_square(data, x, y, size);
		y += size;
		i++;
	}
	return (x);
}

int	draw_line_hor(t_data *data, int x, int y, int size)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		x += draw_square(data, x, y, size);
		i++;
	}
	return (x);
}
