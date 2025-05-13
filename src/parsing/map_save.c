/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:25:11 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/13 10:58:58 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_check(int fd, char *line, t_data *data)
{
	int	i;
	char	*prev;
	int	not_first;
	char	*next;

	i = 0;
	not_first = 0;
	next = get_next_line(fd);
	while (line != NULL)
	{
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
	int	check;
	int	height;
	int	lenght;
	int	max_lenght;

	max_lenght = 0;

	while (line != NULL)
	{
		lenght = 0;
		check = 0;
		while (line[i] != '\n')
		{
			if (line[i] == '1' || line[i] == '0' && check == 0)
				check++;
			lenght++;
		}
		if (lenght > max_lenght)
			max_lenght = lenght;
	}
	data->sizes.map_height = height;
	data->sizes.map_lenght = max_lenght;
}

int	get_map(int fd, int gnl_calls, t_data *data)
{
	int	i;
	char	*line;

	i = 0;
	while (i < gnl_calls)
	{
		line = get_next_line(fd);
		i++;
	}
	if (map_check(fd, line, data))
		return (0);
	close(fd);
	get_next_line(-1);
	while (i < gnl_calls)
	{
		line = get_next_line(fd);
		i++;
	}
	get_sizes(fd, line, data);
	return (1);
}