#include "../includes/flap.h"

static void	init_img_file(t_data *data, t_img *img)
{
	void	*texture;
	char	*path;

	path = img->path;
	texture = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	img->img = texture;
	img->tex_data = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	init_imgs(t_data *data)
{
	init_img_file(data, data->bg);
	init_img_file(data, data->bird);
	init_img_file(data, data->pipe_top);
	init_img_file(data, data->pipe_bot);
}

void	init_move(t_data *data, t_move *move)
{
	int		i;
	float	pos;

	move->delta_time = 0.016f;
	move->bird_y = data->bird->y;
	move->bird_velocity = 0.0f;
	move->gravity = 300;
	move->flap_strength = -200;
	move->flap = 0;
	move->pipe_velocity = 200.0f;
	move->pipe_gap_y = data->bird->height * 2;
	move->pipe_gap_x = 200;
	//move->pipe_gap_x = (WINDOW_WIDTH / data->pipe_top->width);
	move->n_pipes = ((WINDOW_WIDTH / (data->pipe_top->width + move->pipe_gap_x)) + 1);
	move->pipe_pos_x = malloc(sizeof(int) * move->n_pipes);
	move->pipe_pos_y = malloc(sizeof(int) * move->n_pipes);
	move->pipe_score = malloc(sizeof(int) * move->n_pipes);
	move->spawn_pipe = data->pipe_top->width;
	
	i = 0;
	while (i < move->n_pipes)
	{
		pos = (move->spawn_pipe + move->pipe_gap_x) * (i + 1) + WINDOW_WIDTH;
		move->pipe_pos_x[i] = pos;
		move->pipe_pos_y[i] = calc_pipe_y(data, move);
		move->pipe_score[i] = 0;
		i++;
		printf("pos: %f\n", pos);
	}

	printf("ytuhhh %i, %i\n", move->n_pipes, move->pipe_gap_x);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->error = false;
	data->errstr = ft_strdup("");
	data->file = NULL;
	data->frame = 0;
	data->gameover = 0;
	data->score = 0;
	data->tcolor = 0;
	data->tcolorbool = false;
	data->move = malloc(sizeof(t_move));
	data->bg = malloc(sizeof(t_img));
	data->bird = malloc(sizeof(t_img));
	data->pipe_top = malloc(sizeof(t_img));
	data->pipe_bot = malloc(sizeof(t_img));
	data->bg->path = NULL;
	data->bird->path = NULL;
	data->pipe_top->path = NULL;
	data->pipe_bot->path = NULL;
	data->bird->x = WINDOW_WIDTH * 0.1;
	data->bird->y = (int)floor(WINDOW_HEIGHT / 2);
	data->pipe_top->x = 0;
	data->pipe_top->y = 0;
	data->pipe_bot->x = 0;
	data->pipe_bot->y = 0;

}
