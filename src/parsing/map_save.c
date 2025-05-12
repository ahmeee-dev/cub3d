/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:25:11 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/12 11:39:28 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_check(int fd, t_data *data)
{
	int	i;
	int	check;

	
}

//doesn't check for errors, just for height
void	get_sizes(int fd, char *line, t_data *data)
{
	int	i;
	int	check;
	int	height;
	int	lenght;
	int	max_lenght;

	max_lenght = 0;

	while (line != NULL)
	{
		lenght = 0;
		check = 0;
		while (line[i] != '\n')
		{
			if (line[i] == '1' || line[i] == '0' && check == 0)
				check++;
			lenght++;
		}
		if (lenght > max_lenght)
			max_lenght = lenght;
	}
	data->sizes.map_height = height;
	data->sizes.map_lenght = max_lenght;
}

int	map_save(int fd, int gnl_calls, t_data *data)
{
	int	i;
	char	*line;

	i = 0;
	while (i < gnl_calls)
	{
		line = get_next_line(fd);
		i++;
	}
	map_check(fd, data);
	close(fd);
	get_next_line(-1);
	while (i < gnl_calls)
	{
		line = get_next_line(fd);
		i++;
	}
	get_sizes(fd, line, data);
;


}