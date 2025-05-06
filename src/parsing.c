/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:26 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/06 16:59:12 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_image(int *i, char *nt, char *line)
{
	int	j;

	j = 2;
	//prendi da line il path per lo sprite dell'immagie + controlla che finisca con .xml
	(*i)++;
}

void	get_colors(char *file, t_colors *colors)
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
			save_image(&i, &colors->floor, line);
		line = get_next_line(fd);
	}
	if (i != 6)
		error_function(); //still to create
}

char	**map_parsing(char *file, t_colors *colors)
{
	errors_checks(file);
	get_colors(file, colors);
	
}