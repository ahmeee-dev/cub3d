/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:28:36 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/16 10:35:13 by ahabdelr         ###   ########.fr       */
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
		i = 0;
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] == ' ')
				matrix[j] = 2;
			else if (line[i] == '0')
				matrix[j] = 0;
			else if (line[i] == '1')
				matrix[j] = 1;
			else if (is_player(line[i]))
				matrix[j] = (int)line[i];
			i++;
			j++;
		}
		if (line[i] == '\n' || line[i] == '\0')
		{
			while (i < map->sizes.map_lenght)
			{
				matrix[j] = 2;
				j++;
				i++;
			}
		}
		free_function(line);
		line = get_next_line(fd);
	}
}

void	matrix_creation(t_map *map, int fd, int gnl_calls)
{
	map->matrix = (int *)malloc(sizeof(int) * (map->sizes.map_height
				* map->sizes.map_lenght));
	matrix_population(map->matrix, fd, gnl_calls, map);
	// int	i = 0;
	// while (i < map->sizes.map_height * map->sizes.map_lenght)
	// {
	// 	ft_printf("%d ", map->matrix[i++]);
	// 	if (i % map->sizes.map_lenght == 0)
	// 		ft_printf("\n");
	// }
}

// Problem: the map in the file doesn't have every line filled to the end,
	that means that I personally have
// to check that every line is filled to the end, and, in case,
	to fill it actively
