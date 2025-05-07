/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:41 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/07 10:50:36 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	mymlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*tmp_addr;

	if (x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT)
	{
		tmp_addr = data->pic.img.addr + (y * data->pic.img.lenght \
			+ x * (data->pic.img.bits_pp / 8));
		*((unsigned int *)tmp_addr) = color;
	}
}

int	mymlx_render(t_mlx *data)
{
	ft_bzero(data->pic.img.addr, WIDTH * HEIGHT * \
			(data->pic.img.bits_pp / 8));

	/*	TODO:
	**	plot the map
	*/

	mlx_put_image_to_window(data->mlx_p, data->pic.win.p, \
							data->pic.img.p, 0, 0);
	return (0);
}

int	mymlx_exit(t_mlx *data)
{
	exit (mymlx_destroy(data));
}
