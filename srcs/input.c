#include "../includes/flap.h"

bool	check_name(char *name)
{
	int		i;
	char	*str;

	str = name;
	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]) || str[i] == ' ' || str[i] == ';'
				|| str[i] == '*')
			return (false);
		i++;
	}
	return (true);
}

int	bird_flap(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_flap_loop(data);
	else if (data->giving_input == false)
	{
		if (keycode == 32)
		{
			if (!data->gameover)
				data->move->flap = 1;
			else
				restart_game(data, data->move);
		}
		else if (keycode == 65293)
			restart_game(data, data->move);
	}
	else if (data->giving_input)
	{
		if (keycode == 65288)
			remove_input(data, 1);
		else if (keycode == 65293)
		{
			add_player_score(data);
			data->giving_input = false;
			free(data->player_name);
			data->player_name = ft_strdup("");
		}
		else if (ft_isascii(keycode) && keycode != 32)
			update_input(data, keycode);
	}
	return (0);
}

int	get_middle_x(t_data *data, char *str, int size)
{
	int	x;

	x = (WINDOW_WIDTH / 2) - (get_string_width(data, str, size) / 2);
	return (x);
}

int	update_input(t_data *data, char c)
{
	char	*join;

	join = ft_strjoin(data->player_name, &c);
	free(data->player_name);
	data->player_name = join;
	return (0);
}

void	remove_input(t_data *data, int size)
{
	char	*newstr;
	int		i;

	if (ft_strlen(data->player_name) < size)
		return ;
	newstr = malloc(sizeof(char) * (ft_strlen(data->player_name) - size));
	i = 0;
	while (i < ft_strlen(data->player_name) - size)
	{
		newstr[i] = data->player_name[i];
		i++;
	}
	newstr[i] = '\0';
	free(data->player_name);
	data->player_name = newstr;
}

void	draw_typingscreen(t_data *data)
{
	float	offset;
	int		size;
	int		x;
	int		y;
	char	*str;
	char	*itoa;

	offset = 0.1;

	str = "game over";
	size = 20;
	x = get_middle_x(data, str, size);
	y = WINDOW_HEIGHT * offset;
	draw_sentence(data, str, x, y, size);

	itoa = ft_itoa(data->score);
	str = ft_strjoin("score: " , itoa);
	y += size * 6;
	size = 15;
	x = get_middle_x(data, str, size);
	draw_sentence(data, str, x, y, size);
	free(str);
	free(itoa);

	str = ft_strjoin("enter name: ", data->player_name);
	y += 6 * size;
	size = 12;
	x = get_middle_x(data, str, size);
	draw_sentence(data, str, x, y, size);
	free(str);
}
