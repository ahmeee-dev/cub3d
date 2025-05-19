/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:25:11 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/19 12:47:00 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 0 se superato, 1 se fallito
int	surround_check(char *line, char *prev, char *next, int i)
{
	if (i == 0 || !next)
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
	if ((next[i] != '1' && next[i] != '0' && !is_player(next[i])))
		return (1);
	if ((next[i + 1] != '1' && next[i + 1] != '0' && !is_player(next[i + 1])))
		return (1);
	if ((next[i - 1] != '1' && next[i - 1] != '0' && !is_player(next[i - 1])))
		return (1);
	return (0);
}

int	map_check(int fd, char *line)
{
	char	*prev;
	char	*next;
	int		player;

	player = 0;
	prev = NULL;
	next = get_next_line(fd);
	while (line != NULL)
	{
		if (check_helper(line, prev, next, &player))
			return (1);
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
	while (line[0] == '\n')
	{
		free_function(line);
		line = get_next_line(fd);
	}
	sizes_helper(line, fd, map);
}

int	get_map(char *file, int gnl_calls, t_map *map)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(file, O_RDONLY);
	line = gnl_helper(line, gnl_calls, fd);
	if (map_check(fd, line))
		return (0);
	close(fd);
	get_next_line(-1);
	fd = open(file, O_RDONLY);
	line = NULL;
	line = gnl_helper(line, gnl_calls, fd);
	get_sizes(fd, line, map);
	return (1);
}
