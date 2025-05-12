/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:39:08 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/12 10:04:48 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1 is for images, 2 is for colors
int	check_safe(char *line, int type)
{
	int	j;
	
	j = 0;
	while (ft_isalnum(line[j]))
		j++;
	while (line[j] == ' ')	
		j++;
	while (ft_isalnum(line[j]) || (type == 1 && line[j] == '_' ) || (type == 2 && line[j] == ','))
		j++;
	while (line[j] == ' ')	
		j++;
	if (line[j] == '\n')
		return (1);
	return (0);
}

int	color_value(char *line)
{
	int	value;
	int	j;

	value = 0;
	j = 1; //start directly after element's name
		value |= (ft_atoi(line + j) << 16);
	while (line[j] != ',')
		j++;
	value |= (ft_atoi(line + (++j)) << 8);
		while (line[j] != ',')
		j++;
	value |= (ft_atoi(line + (++j)));
	return (value);
}


void	save_color(int *i, int *dest, char *line)
{
	int	j;
	int	check;
	int	commas;

	if (!check_safe(line, 1))
		error_function(); //still to create
	check = 0;
	commas = 0;
	j = 1;
	while (line[j] == ' ')
		j++;
	while(line[j] != '\n' && line[j] != ' ' && line[j] != '\0')
	{
		if (ft_isnum(line[j]))
			check++;
		if (check >= 1 && check <= 3 && line[j] == ',') //check = 0 non ci sono cifre, check > 3 ce ne sono troppe
		{
			check = 0;
			commas++;
		}
		j++;
	}
	if (commas != 2 || check == 0 || check > 3)
		error_function(); //still to create, wrong format
	(*i)++;
	*dest = color_value(line);
}

void	get_path(int *i, char **dest, char *line)
{
	line = ft_strstr(line, "./");
	if (!line)
		error_function(); //still to create, No path
	*dest = ft_strtrim(line, "./\n");
	(*i)++;
	if (!check_safe(line, 1))
		error_function(); //still to create, wrong format
}

void	get_graphics(char *file, t_colors *colors)
{
	int	fd;
	char	*line;
	int	i;
	int	gnl_calls;

	fd = open(file);
	line = get_next_line(line);
	i = 0;
	while (line != NULL)
	{
		if (ft_strnstr(line, "NT", 2))
			save_image(&i, &colors->nt, line); 
		else if (ft_strnstr(line, "ST", 2))
			save_image(&i, &colors->st, line);
		else if (ft_strnstr(line, "ET", 2))
			save_image(&i, &colors->et, line);
		else if (ft_strnstr(line, "WT", 2))
			save_image(&i, &colors->wt, line);
		else if (ft_strnstr(line, "c", 1))
			save_color(&i, &colors->ceiling, line);
		else if (ft_strnstr(line, "f", 1))
			save_color(&i, &colors->floor, line);
		line = get_next_line(fd);
		if (i < 6)
			gnl_calls++;
	}
	if (i != 6)
		error_function(); //still to create, too much data before the map
	return (gnl_calls);
}