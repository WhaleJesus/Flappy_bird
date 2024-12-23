/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:39:23 by sklaps            #+#    #+#             */
/*   Updated: 2024/12/23 20:00:18 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/flap.h"

char	*strip_soh(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '\n' || str[i] == '\t'
				|| str[i] == 47 || str[i] >= 32)
			j++;
		i++;
	}
	tmp = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '\n' || str[i] == '\t'
				|| str[i] == 47 || str[i] >= 32)
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	printf("%s\n", tmp);
	return (tmp);
}

char	*strip_ws(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
			j++;
		i++;
	}
	tmp = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

bool	check_extension(char *path, char *ext)
{
	char	*tmp;
	int		check;

	tmp = ft_strjoin(".", ext);
	path += ft_strlen(path) - 4;
	check = ft_strncmp(path, tmp, 5);
	free(tmp);
	if (check)
		return (false);
	return (true);
}

char	*check_img(t_data *data, char *path)
{
	int		fd;
	char	*msg;

	msg = NULL;
	path = strip_ws(path);
	fd = open(path, O_RDONLY);
	if (!check_extension(path, "xpm"))
	{
		msg = ft_strjoin("Extension should be .xpm ", path);
		add_error(data, msg);
	}
	else if (fd < 1)
	{
		msg = ft_strjoin("Could not open file ", path);
		add_error(data, msg);
	}
	if (fd > 0)
		close(fd);
	if (msg)
		return (free(msg), free(path), NULL);
	return (path);
}

char	**read_file(t_data *data, char *path, int rd)
{
	int		fd;
	char	buf;
	char	*wholefile;
	char	*error;
	char	*tmp;
	char	**ret;

	wholefile = ft_strdup("");
	if (!wholefile)
		add_error(data, "Malloc failed");
	fd = open(path, O_RDONLY);
	if (fd < 0 || !fd || !wholefile)
	{
		if (fd > 0)
			close(fd);
		else
		{
			error = ft_strjoin("Could not open file ", path);
			add_error(data, error);
		}
		if (wholefile)
			free(wholefile);
		exit_flap(data, NULL, true);
	}
	while (rd > 0)
	{
		rd = read(fd, &buf, 1);
		tmp = wholefile;
		wholefile = ft_strjoin(wholefile, &buf);
		free(tmp);
	}
	tmp = strip_soh(wholefile);
	ret = ft_split(tmp, '\n');
	if (!ret)
		ret = NULL;
	if (fd > 0)
		close(fd);
	return (free(wholefile), free(tmp), ret);
}

void	print_file(t_data *data, char **file)
{
	int	i;
	
	i = 0;
	while (file[i])
	{
		printf("%s\n", file[i]);
		i++;
	}
	data->error = true;
}

int	parse_hex(t_data *data, char *str)
{
	int		ret;
	char	*conv_str;

	conv_str = strip_ws(str);
	ret = (int)strtol(str, NULL, 16);
	free(conv_str);
	if (!ret)
		return (0);
	data->tcolorbool = true;
	//printf("%x\n",ret);
	return (ret);
}

void	store_settings(t_data *data, char **file)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (file[i])
	{
		if (!ft_strncmp("BG", file[i], 2))
			data->bg->path = check_img(data, file[i] + ft_strlen("BG"));
		if (!ft_strncmp("PIPE TOP", file[i], 8))
			data->pipe_top->path = check_img(data, file[i] + ft_strlen("PIPE TOP"));
		if (!ft_strncmp("PIPE BOT", file[i], 8))
			data->pipe_bot->path = check_img(data, file[i] + ft_strlen("PIPE BOT"));
		if (!ft_strncmp("BIRD", file[i], 4))
			data->bird->path = check_img(data, file[i] + ft_strlen("BIRD"));
		if (!ft_strncmp("TCOLOR", file[i], ft_strlen("TCOLOR")))
			data->tcolor = parse_hex(data, file[i] + ft_strlen("TCOLOR"));
		if (!ft_strncmp("LETTERS", file[i], ft_strlen("LETTERS")))
		{
			str = strip_ws(file[i] + ft_strlen("LETTERS"));
			data->letters = read_file(data, str, 1);
		}
		if (!ft_strncmp("HISCORE", file[i], ft_strlen("HISCORE")))
		{
			str = strip_ws(file[i] + ft_strlen("HISCORE"));
			data->file_hiscore = read_file(data, str, 1);
			data->hiscore_path = ft_strdup(str);
		}
		if (str)
			free(str);
		i++;
	}
}

void	check_file(t_data *data, char *path)
{
	data->file = read_file(data, path, 1);
	store_settings(data, data->file);
//	print_file(data, data->letters);
	if (data->error)
		exit_flap(data, NULL, true);
}
