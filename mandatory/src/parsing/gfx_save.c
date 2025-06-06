/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:39:08 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/21 09:04:23 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_safe(char *line, int type)
{
	int	j;

	j = 0;
	while (ft_isalnum(line[j]))
		j++;
	while (line[j] == ' ')
		j++;
	if (line[j] == '.')
		j++;
	if (line[j] == '/')
		j++;
	while (ft_isalnum(line[j]) || (type == 1 && (line[j] == '_'
				|| line[j] == '.' || line[j] == '/')) || (type == 2
			&& line[j] == ','))
		j++;
	while (line[j] == ' ')
		j++;
	if (line[j] == '\n')
		return (0);
	return (1);
}

int	color_value(char *line)
{
	int	value;
	int	j;

	value = 0;
	j = 1;
	value |= (ft_atoi(line + j) << 16);
	while (line[j] != ',')
		j++;
	value |= (ft_atoi(line + (++j)) << 8);
	while (line[j] != ',')
		j++;
	value |= (ft_atoi(line + (++j)));
	return (value);
}

int	save_color(int *i, int *dest, char *line)
{
	int	j;

	if (check_safe(line, 2))
		return (1);
	j = 1;
	while (line[j] == ' ')
		j++;
	if (color_helper(line, j))
		return (1);
	(*i)++;
	*dest = color_value(line);
	return (0);
}

int	save_image(int *i, char **dest, char *line)
{
	line = ft_strstr(line, "./");
	if (!line)
		return (1);
	*dest = ft_strtrim(line, "./\n");
	(*i)++;
	if (check_safe(line, 1))
		return (1);
	return (0);
}

int	get_graphics(char *file, t_map *map)
{
	char	*line;
	int		i;
	int		gnl_calls;
	int		result[7];

	result[0] = open(file, O_RDONLY);
	if (result[0] == -1)
		return (0);
	gnl_calls = 1;
	line = get_next_line(result[0]);
	i = graphics_helper(line, &gnl_calls, result, map);
	if (i != 6)
		return (0);
	i = 1;
	while (i < 7)
		if (result[i++] == 1)
			return (0);
	return (gnl_calls + 1);
}
