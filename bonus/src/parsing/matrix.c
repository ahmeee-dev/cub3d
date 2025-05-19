/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:28:36 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/19 11:48:30 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_player(char c);

void	matrix_population(int *matrix, int fd, int gnl_calls, t_map *map)
{
	char	*line;
	int		i;
	int		j;

	i = 1;
	j = 0;
	line = get_next_line(fd);
	while (i++ < gnl_calls)
	{
		free_function(line);
		line = get_next_line(fd);
	}
	while (line[0] == '\n')
	{
		free_function(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		matrix_helper(line, matrix, &j, map);
		free_function(line);
		line = get_next_line(fd);
	}
}

void	matrix_creation(t_map *map, int fd, int gnl_calls)
{
	map->matrix = (int *)malloc(sizeof(int) * (map->sizes.map_height
				* map->sizes.map_lenght));
	matrix_population(map->matrix, fd, gnl_calls, map);
}
