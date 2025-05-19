/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:39:28 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/19 11:07:48 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_function(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
}

int	is_player(char c)
{
	if (c == 'W' || c == 'S' || c == 'E' || c == 'N')
		return (1);
	return (0);
}

int	color_helper(char *line, int j)
{
	int	commas;
	int	check;

	commas = 0;
	check = 0;
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
	return (0);
}
