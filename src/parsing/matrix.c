/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:28:36 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/13 14:53:09 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	matrix_population(int *matrix, int fd, int gnl_calls)
{
	char	*line;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i++ < gnl_calls + 1)
		line = get_next_line(fd);
	i = 0;
	while (line)
	{
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] == ' ')
				matrix[j] = -1;
			else if (line[i] == '0')
				matrix[j] = 0; 
			else if (line[i] == '1')
				matrix[j] = 1;
			i++;
			j++;
		}
		line = get_next_line(fd);
	}
}

void	matrix_creation(t_data *data, int fd, int gnl_calls)
{
	data->matrix = (int *)malloc(sizeof(int) * (data->sizes.map_height * data->sizes.map_lenght));
	matrix_population(data->matrix, fd, gnl_calls);

	for (int i = 0; i < data->sizes.map_height * data->sizes.map_lenght; i++)
	{
		ft_printf("%d ", data->matrix[i]);
	}
}