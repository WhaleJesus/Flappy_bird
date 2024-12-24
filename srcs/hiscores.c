#include "../includes/flap.h"

void	print_list(t_hiscore **hiscore)
{
	t_hiscore	*head;

	head = *hiscore;
	while (head->prev)
		head = head->prev;
	while (head)
	{
//		printf("%s %i\n", head->name, head->score);
		head = head->next;
	}
	//while (head->prev)
	//	head = head->prev;
	//*hiscore = head;
}

t_hiscore	*new_node(char *name, int score)
{
	t_hiscore	*hiscore;
	char		*tmp;

	tmp = ft_strjoin(name, ";");
	if (!ft_strncmp(tmp, ";", 1))
		return (free(tmp), NULL);
	hiscore = malloc(sizeof(t_hiscore));
	if (!hiscore || !name || score < 0)
		return (NULL);
	hiscore->name = ft_strdup(name);
	hiscore->score = score;
	hiscore->prev = NULL;
	hiscore->next = NULL;
	//printf("%s %i\n", hiscore->name, hiscore->score);
	return (hiscore);
}

void	add_node(t_hiscore *hiscore, char *name, int score)
{
	t_hiscore	*new;
	t_hiscore	*head;
	t_hiscore	*tmp;
	t_hiscore	*tmp2;

	head = hiscore;
	while (head->prev)
		head = head->prev;
	new = new_node(name, score);
	if (!new)
		return ;
	tmp2 = head;
	while (tmp2)
	{
		if (!ft_strncmp(tmp2->name, new->name, ft_strlen(new->name)))
		{
			if (head->score <= new->score)
			{
				tmp2->prev->next = tmp2->next;
				tmp2->next->prev = tmp2->prev;
				tmp = tmp2->next;
				free(tmp2->name);
				free(tmp2);
				tmp2 = tmp;
				break ;
			}
			else
			{
				free(new->name);
				free(new);
				return ;
			}
		}
		tmp2 = tmp2->next;
	}
	while (head)
	{
		if (head->score <= new->score)
		{
			new->next = head;
			if (head->prev)
				new->prev = head->prev;
			head->prev = new;
			if (new->prev)
				new->prev->next = new;
			if (new->next)
				new->next->prev = new;
			break ;
		}
		if (!head->next)
		{
			head->next = new;
			new->prev = head;
			break ;
		}
		else
			head = head->next;
	}
	while (head->prev)
		head = head->prev;
	hiscore = head;
	print_list(&hiscore);
}

void	free_char_arr(char **bruh)
{
	int	i;

	if (!bruh)
		return ;
	i = 0;
	while (bruh[i])
		free(bruh[i++]);
	free(bruh);
}



void	free_hiscore(t_hiscore *hiscore)
{
	t_hiscore	*tmp;

	while (hiscore)
	{
		tmp = hiscore->next;
		free(hiscore->name);
		free(hiscore);
		hiscore = tmp;
	}
}

void	add_player_score(t_data *data)
{
	int	score;

	score = (int)data->score;
	if (!data->hiscore)
		data->hiscore = new_node(data->player_name, score);
	else
		add_node(data->hiscore, data->player_name, score);
	data->hiscore = get_head(data->hiscore);
//	print_list(&data->hiscore);
}

void	write_hiscore(t_data *data)
{
	t_hiscore	*head;
	int			fd;
	char		*tmp;
	char		*tmp2;
	char		*writestr;

	if (!data->hiscore)
		return ;
	head = get_head(data->hiscore);
	fd = open(data->hiscore_path, O_WRONLY | O_TRUNC);
	if (!fd || fd < 1)
		return ;
	while (head)
	{
		tmp = ft_strjoin(head->name, "=");
		tmp2 = ft_itoa(head->score);
		writestr = ft_strjoin(tmp, tmp2);
		write(fd, writestr, ft_strlen(writestr));
		write(fd, "\n", 1);
		head = head->next;
		free(tmp);
		free(tmp2);
		free(writestr);
	}
	close(fd);
}

t_hiscore	*get_head(t_hiscore *hiscore)
{
	while (hiscore->prev)
		hiscore = hiscore->prev;
	return (hiscore);
}

t_hiscore	*make_list(char **arr)
{
	t_hiscore	*hiscore;
	int			i;
	int			score;
	char		**bruh;

	if (!arr)
		return (printf("no arr\n"),NULL);
	bruh = ft_split(arr[0], '=');
	if (!bruh)
		return (NULL);
	hiscore = new_node(bruh[0], ft_atoi(bruh[1]));
	free_char_arr(bruh);
	i = 1;
	while (arr[i])
	{
		bruh = ft_split(arr[i], '=');
		add_node(hiscore, bruh[0], ft_atoi(bruh[1]));
		free_char_arr(bruh);
		i++;
	}
	//print_list(&hiscore);
	return (hiscore);
}
