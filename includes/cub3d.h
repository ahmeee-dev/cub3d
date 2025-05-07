/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/07 11:12:48 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WIDTH 1920
#define HEIGHT 1080

#include "../libft/includes/libft.h"
#include "../.minilibx/minilibx_opengl_20191021/mlx.h"
#include "../.minilibx/minilibx_opengl_20191021/mlx_int.h"
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
