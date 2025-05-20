/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:38:36 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/20 11:11:59 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	first_half(char *line, int *result, t_map *map, int *i)
{
	if (ft_strnstr(line, "WA", 2))
		result[1] = save_image(i, &map->data.wall, line);
	else if (ft_strnstr(line, "G1", 2))
		result[2] = save_image(i, &map->data.gun1, line);
	else if (ft_strnstr(line, "G2", 2))
		result[3] = save_image(i, &map->data.gun1, line);
	else if (ft_strnstr(line, "DO", 2))
		result[4] = save_image(i, &map->data.door, line);
	else if (ft_strnstr(line, "C1", 1))
		result[5] = save_image(i, &map->data.ceiling1, line);
	else if (ft_strnstr(line, "C2", 1))
		result[6] = save_image(i, &map->data.ceiling2, line);
	else if (ft_strnstr(line, "C3", 1))
		result[7] = save_image(i, &map->data.ceiling3, line);
	else if (ft_strnstr(line, "HA", 1))
		result[8] = save_image(i, &map->data.hand, line);
	else if (ft_strnstr(line, "F1", 1))
		result[9] = save_image(i, &map->data.floor1, line);
	else if (ft_strnstr(line, "F2", 1))
		result[10] = save_image(i, &map->data.floor2, line);
	else if (ft_strnstr(line, "F3", 1))
		result[11] = save_image(i, &map->data.floor3, line);
	else if (ft_strnstr(line, "F4", 1))
		result[12] = save_image(i, &map->data.floor4, line);
}

int	graphics_helper(char *line, int *gnl_calls, int *result, t_map *map)
{
	int	i;

	i = 0;
	while (line != NULL)
	{
		first_half(line, result, map, &i);
		if (ft_strnstr(line, "F5", 1))
			result[13] = save_image(&i, &map->data.floor5, line);
		else if (ft_strnstr(line, "F6", 1))
			result[14] = save_image(&i, &map->data.floor6, line);
		if (ft_strnstr(line, "F7", 1))
			result[15] = save_image(&i, &map->data.floor7, line);
		else if (ft_strnstr(line, "F8", 1))
			result[16] = save_image(&i, &map->data.floor8, line);
		free_function(line);
		line = get_next_line(result[0]);
		if (i < 17)
			(*gnl_calls)++;
	}
	return (i);
}
