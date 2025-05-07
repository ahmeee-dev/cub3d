/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:39:08 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/07 11:00:22 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_value(char *line)
{
	int	value;
	int	j;

	value = 0;
	j = 2; //start directly after element's name
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

	check = 0;
	commas = 0;
	j = 2;
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
		error_function(); //still to create
	(*i)++;
	*dest = color_value(line);
}

void	get_images(char *file, t_colors *colors)
{
	int	fd;
	char	*line;
	int	i;

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
		else if (ft_strnstr(line, "c", 2))
			save_color(&i, &colors->ceiling, line);
		else if (ft_strnstr(line, "f", 2))
			save_color(&i, &colors->floor, line);
		line = get_next_line(fd);
	}
	if (i != 6)
		error_function(); //still to create
}