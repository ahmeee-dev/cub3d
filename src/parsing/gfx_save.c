/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:39:08 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/16 10:33:30 by ahabdelr         ###   ########.fr       */
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
	int	check;
	int	commas;

	if (check_safe(line, 2))
		return (1);
	check = 0;
	commas = 0;
	j = 1;
	while (line[j] == ' ')
		j++;
	while (line[j] != '\n' && line[j] != ' ' && line[j] != '\0')
	{
		if (ft_isnum(line[j]))
			check++;
		if (check >= 1 && check <= 3 && line[j] == ',')
		{
			check = 0;
			commas++;
		}
		j++;
	}
	if (commas != 2 || check == 0 || check > 3)
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
	i = 0;
	while (line != NULL)
	{
		if (ft_strnstr(line, "NO", 2))
			result[0] = save_image(&i, &map->data.nt, line);
		else if (ft_strnstr(line, "SO", 2))
			result[1] = save_image(&i, &map->data.st, line);
		else if (ft_strnstr(line, "EA", 2))
			result[2] = save_image(&i, &map->data.et, line);
		else if (ft_strnstr(line, "WE", 2))
			result[3] = save_image(&i, &map->data.wt, line);
		else if (ft_strnstr(line, "c", 1))
			result[4] = save_color(&i, &map->data.ceiling, line);
		else if (ft_strnstr(line, "f", 1))
			result[5] = save_color(&i, &map->data.floor, line);
		free_function(line);
		line = get_next_line(fd);
		if (i < 6)
			gnl_calls++;
	}
	if (i != 6)
		return (0);
	i = 0;
	while (i < 6)
		if (result[i++] == 1)
			return (0);
	return (gnl_calls + 1);
}
