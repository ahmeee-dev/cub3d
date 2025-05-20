/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:26 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/20 13:17:34 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1 = success, 0 = failure
int	map_parsing(char *file, t_map *map)
{
	int	gnl_calls;
	int	fd;

	gnl_calls = get_graphics(file, map);
	if (!gnl_calls)
		return (0);
	get_next_line(-1);
	fd = open(file, O_RDONLY);
	if (!get_map(file, gnl_calls, map))
		return (0);
	close(fd);
	get_next_line(-1);
	fd = open(file, O_RDONLY);
	matrix_creation(map, fd, gnl_calls);
	return (1);
}
