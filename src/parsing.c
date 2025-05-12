/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:26 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/12 11:15:31 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



char	**map_parsing(char *file, t_colors *colors, t_data *data)
{
	int	gnl_calls;
	int	fd;

	errors_checks(file);
	gnl_calls = get_graphics(file, &data->colors);
	get_next_line(-1);
	fd = open(file);
	get_map(fd, gnl_calls, data);
}