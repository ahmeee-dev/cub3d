/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:25:11 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/14 14:43:36 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'W' || c == 'S' || c == 'E' || c == 'N')
		return (1);
	return (0);
}

// 0 se superato, 1 se fallito
int	surround_check(char *line, char *prev, char *next, int i)
{
	if (i == 0)
		return (1);
	if ((line[i - 1] != FLOOR && line[i - 1] != WALL && !is_player(line[i - 1]) && !is_player(line[i - 1])))
		return (1);
	if ((line[i + 1] != FLOOR && line[i + 1] != WALL && !is_player(line[i + 1]) && !is_player(line[i + 1])))
		return (1);
	if ((prev[i] != WALL && prev[i] != FLOOR && !is_player(prev[i]) && !is_player(prev[i])))
		return (1);
	if ((prev[i + 1] != WALL && prev[i + 1] != FLOOR && !is_player(prev[i + 1]) && !is_player(prev[i + 1])))
		return (1);
	if ((prev[i - 1] != WALL && prev[i - 1] != FLOOR && !is_player(prev[i - 1]) && !is_player(prev[i - 1])))
		return (1);
	if (!next || (next[i] != WALL && next[i] != FLOOR && !is_player(next[i]) && !is_player(next[i])))
		return (1);
	if (!next || (next[i + 1] != WALL && next[i + 1] != FLOOR && !is_player(next[i + 1]) && !is_player(next[i + 1])))
		return (1);
	if (!next || (next[i - 1] != WALL && next[i - 1] != FLOOR && !is_player(next[i - 1]) && !is_player(next[i - 1])))
		return (1);
	return (0);
}

// da integrare tolleranza per il Player
int	map_check(int fd, char *line)
{
	int	i;
	char	*prev;
	int	not_first;
	char	*next;
	int	player;

	i = 0;
	player = 0;
	next = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		not_first = 0;
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] == WALL)
				not_first++;
			if (line[i] == FLOOR)
			{
				if (!not_first)
					return (1);
				if (surround_check(line, prev, next, i))
					return (1);
			}
			if (line[i] == 'W' || line[i] == 'S' || line[i] == 'N' || line[i] == 'A')
				player++;
			i++;
		}
		prev = line;
		line = next;
		next = get_next_line(fd);
	}
	if (player != 1)
		return (1);
	return (0);
}

void	get_sizes(int fd, char *line, t_data *data)
{
	int	i;
	int	height;
	int	lenght;
	int	max_lenght;

	i = 0;
	max_lenght = 0;
	height = 0;
	while (line[0] == '\n')
		line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		height++;
		lenght = 0;
		while (line[i] != '\n' && line[i] != '\0')
		{
			i++;
			lenght++;
		}
		if (lenght > max_lenght)
			max_lenght = lenght;
		line = get_next_line(fd);
	}
	data->sizes.map_height = height;
	data->sizes.map_lenght = max_lenght;
}

int	get_map(char *file, int gnl_calls, t_data *data)
{
	int	i;
	char	*line;
	int	fd;

	fd = open(file, O_RDONLY);
	i = 0;
	while (i < gnl_calls)
	{
		line = get_next_line(fd);
		i++;
	}
	if (map_check(fd, line))
		return (0);
	close(fd);
	get_next_line(-1);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < gnl_calls)
	{
		line = get_next_line(fd);
		i++;
	}
	get_sizes(fd, line, data);
	return (1);
}