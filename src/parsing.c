/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:26 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/05/07 11:10:30 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



char	**map_parsing(char *file, t_colors *colors)
{
	errors_checks(file);
	get_graphics(file, colors);
	
}