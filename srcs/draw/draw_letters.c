/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_letters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 02:59:31 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/23 20:39:42 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/flap.h"

bool	check_letter(char c, char **letters, int x, int y)
{
	int	i;

	i = 0;
	while (letters[i])
	{
		if (letters[i][0] == c)
		{
			if (ft_strlen(letters[i + x]) > 0 && y >= 0)
			{
				if (letters[i + x][y] == '*')
					return (true);
			}
			return (false);
		}
		i++;
	}
	return (false);
}

int	get_letter_width(t_data *data, const char letter)
{
	int	i;
	int	j;

	i = 0;
	while (data->letters[i])
	{
		if (data->letters[i][0] == letter)
		{
			i++;
			j = 0;
			while (data->letters[i][j])
			{
				j++;
			}
			return (j);
		}
		i++;
	}
	return (0);
}

int	draw_letter(t_data *data, char letter, int x, int y, int size)
{
	int	i;
	int	j;
	int	x2;
	int	y2;
	int	width;

	if (letter == '*' || letter == ';')
		return (0);
	width = get_letter_width(data, letter);
	if (width == 0)
		return (0);
	i = 0;
	y2 = y;
	while (i < 5)
	{
		j = 0;
		x2 = x;
		while(j < width)
		{
			if (check_letter(letter, data->letters, i + 1, j))
			{
				if (!check_letter(letter, data->letters, i, j))
					draw_face(data, x2, y, size, 0);
				if (!check_letter(letter, data->letters, i + 2, j))
					draw_face(data, x2, y, size, 2);
				if (!check_letter(letter, data->letters, i + 1, j + 1))
					draw_face(data, x2, y, size, 1);
				if (!check_letter(letter, data->letters, i + 1, j - 1))
					draw_face(data, x2, y, size, 3);
			}
			x2 += size;
			j++;
		}
		y += size;
		i++;
	}
	y = y2;
	i = 0;
	while (i < 5)
	{
		j = 0;
		x2 = x;
		while(j < width)
		{
			if (check_letter(letter, data->letters, i + 1, j))
				draw_square(data, x2, y, size);
			x2 += size;
			j++;
		}
		y += size;
		i++;
	}
	return (j * size);
}

int	get_string_width(t_data *data, char *str, int size)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str[i])
	{
		x += (get_letter_width(data, str[i]) * size) + size;
		i++;
	}
	return (x);
}

int	draw_sentence(t_data *data, char *str, int x, int y, int size)
{
	int	i;

	i = 0;
	while (str[i])
	{
		x += draw_letter(data, str[i], x, y, size);
		x += size;
		i++;
	}
	return (x - size);
}
