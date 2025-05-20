/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:39:08 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/20 13:39:33 by marvin@42.f      ###   ########.fr       */
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
				|| line[j] == '.' || line[j] == '/')) || (type == 2
			&& line[j] == ','))
		j++;
	while (line[j] == ' ')
		j++;
	if (line[j] == '\n')
		return (0);
	return (1);
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
	int		result[17];

	result[0] = open(file, O_RDONLY);
	if (result[0] == -1)
		return (0);
	gnl_calls = 1;
	line = get_next_line(result[0]);
	i = graphics_helper(line, &gnl_calls, result, map);
	if (i != 16)
		return (0);
	i = 1;
	while (i < 17)
		if (result[i++] == 1)
			return (0);
	return (gnl_calls + 1);
}
