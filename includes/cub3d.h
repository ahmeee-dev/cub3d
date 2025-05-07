/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/07 11:10:41 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/includes/libft.h"
#include <unistd.h>

typedef struct	s_colors
{
	int	floor;
	int	ceiling;
	char	*nt;
	char	*st;
	char	*et;
	char	*wt;
}		t_colors;


void	get_graphics(char *file, t_colors *colors);


#endif
