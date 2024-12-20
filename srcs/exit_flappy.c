#include "../includes/flap.h"

void	exit_msg(char *msg)
{
	write(1, msg, ft_strlen(msg));
	free(msg);
	exit(0);
}

void	add_error(t_data *data, char *msg)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("Error: ", msg);
	tmp2 = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = ft_strjoin(data->errstr, tmp2);
	free(tmp2);
	free(data->errstr);
	data->errstr = tmp;
	if (!data->error)
		data->error = true;
}

void	exit_flap(t_data *data, char *msg, bool init)
{
	int	i = 0;

	if (!init)
	{
		mlx_destroy_image(data->mlx, data->bg->img);
		mlx_destroy_image(data->mlx, data->pipe_top->img);
		mlx_destroy_image(data->mlx, data->pipe_bot->img);
		mlx_destroy_image(data->mlx, data->bird->img);
	}

	if (data->bg->path)
		free(data->bg->path);
	if (data->pipe_top->path)
		free(data->pipe_top->path);
	if (data->pipe_bot->path)
		free(data->pipe_bot->path);
	if (data->bird->path)
		free(data->bird->path);

	free(data->bg);
	free(data->pipe_top);
	free(data->pipe_bot);
	free(data->bird);
	free(data->move);

	if (data->file)
	{
		while(data->file[i])
			free(data->file[i++]);
		free(data->file);
	}
	
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);

	if (!msg)
		msg = data->errstr;
	else 
		free(data->errstr);
	exit_msg(msg);
}

int	exit_flap_loop(t_data *data)
{
	exit_flap(data, ft_strdup("See ya\n"), false);
	return (0);
}
