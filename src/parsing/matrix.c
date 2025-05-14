/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:28:36 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/14 15:59:56 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	matrix_population(int *matrix, int fd, int gnl_calls, t_data *data)
{
	char	*line;
	int	i;
	int	j;

	i = 1;
	j = 0;
	line = get_next_line(fd);
	while (i++ < gnl_calls)
	{
		free_function(line);
		line = get_next_line(fd);
	}
	while (line[0] == '\n')
	{
		free_function(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		i = 0;
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] == ' ')
				matrix[j] = 2;
			else if (line[i] == '0')
				matrix[j] = 0; 
			else if (line[i] == '1')
				matrix[j] = 1;
			i++;
			j++;
		}
		if (line[i] == '\n' || line[i] == '\0')
		{
			while (i < data->sizes.map_lenght)
			{
				matrix[j] = 2;
				j++;
				i++;
			}
		}
		free_function(line);
		line = get_next_line(fd);
	}
}

void	matrix_creation(t_data *data, int fd, int gnl_calls)
{
	data->matrix = (int *)malloc(sizeof(int) * (data->sizes.map_height * data->sizes.map_lenght));
	matrix_population(data->matrix, fd, gnl_calls, data);

	// int	i = 0;
	// while (i < data->sizes.map_height * data->sizes.map_lenght)
	// {
	// 	ft_printf("%d ", data->matrix[i++]);
	// 	if (i % data->sizes.map_lenght == 0)
	// 		ft_printf("\n");
	// }
}

// Problem: the map in the file doesn't have every line filled to the end, that means that I personally have
// to check that every line is filled to the end, and, in case, to fill it actively