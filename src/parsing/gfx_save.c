/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:39:08 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/19 11:19:42 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				|| line[j] == '.')) || (type == 2 && line[j] == ','))
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
	int		fd;
	char	*line;
	int		i;
	int		gnl_calls;
	int		result[6];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	gnl_calls = 1;
	line = get_next_line(fd);
	i = graphics_helper(line, &gnl_calls, result);
	if (i != 6)
		return (0);
	i = 0;
	while (i < 6)
		if (result[i++] == 1)
			return (0);
	return (gnl_calls + 1);
}
