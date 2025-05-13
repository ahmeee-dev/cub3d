/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:25:11 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/13 14:42:35 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// da integrare tolleranza per il Player
int	map_check(int fd, char *line)
{
	int	i;
	char	*prev;
	int	not_first;
	char	*next;

	i = 0;
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
				if (i == 0)
					return (1);
				if (line[i - 1] != FLOOR && line[i - 1] != WALL)
					return (1);
				if (line[i + 1] != FLOOR && line[i + 1] != WALL)
					return (1);
				if (!not_first || (prev[i] != WALL && prev[i] != FLOOR))
					return (1);
				if (!not_first || (prev[i + 1] != WALL && prev[i + 1] != FLOOR))
					return (1);
				if (!not_first || (prev[i - 1] != WALL && prev[i - 1] != FLOOR))
					return (1);
				if (!next || (next[i] != WALL && next[i] != FLOOR))
					return (1);
				if (!next || (next[i + 1] != WALL && next[i + 1] != FLOOR))
					return (1);
				if (!next || (next[i - 1] != WALL && next[i - 1] != FLOOR))
					return (1);
			}
			i++;
		}
		prev = line;
		line = next;
		next = get_next_line(fd);
	}
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
	while (i <= gnl_calls + 1)
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
	while (i <= gnl_calls + 1)
	{
		line = get_next_line(fd);
		i++;
	}
	get_sizes(fd, line, data);
	return (1);
}