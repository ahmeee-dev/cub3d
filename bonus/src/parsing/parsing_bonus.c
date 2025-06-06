/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:26 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/21 09:16:44 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
