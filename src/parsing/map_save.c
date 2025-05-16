/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:25:11 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/15 08:14:02 by apintaur         ###   ########.fr       */
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
	//printf("%d in %d\n\n", line[i], i);
	if (i == 0)
		return (1);
	if (line[i - 1] != '1' && line[i - 1] != '0' && !is_player(line[i - 1]))
		return (1);
	if (line[i + 1] != '1' && line[i + 1] != '0' && !is_player(line[i + 1]))
		return (1);
	if (prev[i] != '1' && prev[i] != '0' && !is_player(prev[i]))
		return (1);
	if (prev[i + 1] != '1' && prev[i + 1] != '0' && !is_player(prev[i + 1]))
		return (1);
	if (prev[i - 1] != '1' && prev[i - 1] != '0' && !is_player(prev[i - 1]))
		return (1);
	if (!next || (next[i] != '1' && next[i] != '0' && !is_player(next[i])))
		return (1);
	if (!next || (next[i + 1] != '1' && next[i + 1] != '0' && !is_player(next[i + 1])))
		return (1);
	if (!next || (next[i - 1] != '1' && next[i - 1] != '0' && !is_player(next[i - 1])))
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
	prev = NULL;
	next = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		not_first = 0;
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] == '1')
				not_first++;
			if (line[i] == '0')
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
		if (prev != NULL)
			free_function(prev);
		prev = line;
		line = next;
		next = get_next_line(fd);
	}
	free_function(prev);
	if (player != 1)
		return (1);
	return (0);
}

void	get_sizes(int fd, char *line, t_map *map)
{
	int	i;
	int	height;
	int	lenght;
	int	max_lenght;

	i = 0;
	max_lenght = 0;
	height = 0;
	while (line[0] == '\n')
	{
		free_function(line);
		line = get_next_line(fd);
	}
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
		free_function(line);
		line = get_next_line(fd);
	}
	map->sizes.map_height = height;
	map->sizes.map_lenght = max_lenght;
}

int	get_map(char *file, int gnl_calls, t_map *map)
{
	int	i;
	char	*line;
	int	fd;

	line = NULL;
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < gnl_calls)
	{
		if (line)
			free_function(line);
		line = get_next_line(fd);
		i++;
	}
	if (map_check(fd, line))
		return (0);
	close(fd);
	get_next_line(-1);
	fd = open(file, O_RDONLY);
	i = 0;
	line = NULL;
	while (i < gnl_calls)
	{
		free_function(line);
		line = get_next_line(fd);
		i++;
	}
	get_sizes(fd, line, map);
	return (1);
}
