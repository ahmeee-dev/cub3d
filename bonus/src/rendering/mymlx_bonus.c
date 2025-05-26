/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:00:06 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/26 16:17:15 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mymlx_render(t_cub *cub)
{
	ft_bzero(cub->pic.img.addr, SCREEN_WIDTH * SCREEN_HEIGHT * \
			(cub->pic.img.bits_pp / 8));
	mlx_put_image_to_window(cub->p, cub->pic.win.p, \
							cub->pic.img.p, 0, 0);
	return (0);
}

void	mymlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*tmp_addr;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		tmp_addr = img->addr + (y * img->lenght \
			+ x * (img->bits_pp / 8));
		*((unsigned int *)tmp_addr) = color;
	}
}

int	mymlx_destroy(t_cub *cub)
{
	if (cub)
	{
		mlx_destroy_image(cub->p, cub->pic.img.p);
		mlx_destroy_image(cub->p, cub->textures.wall.p);
		mlx_destroy_image(cub->p, cub->textures.door.p);
		mlx_destroy_image(cub->p, cub->textures.gun_fire.p);
		mlx_destroy_image(cub->p, cub->textures.gun_nofire.p);
		mlx_destroy_image(cub->p, cub->textures.ceiling_light.p);
		mlx_destroy_image(cub->p, cub->textures.ceiling_nolight.p);
		mlx_destroy_image(cub->p, cub->textures.floor_light.p);
		mlx_destroy_image(cub->p, cub->textures.floor_nolight.p);
		mlx_destroy_window(cub->p, cub->pic.win.p);
		free (cub->raycaster.rays);
		if (cub->map.doors_state)
			free(cub->map.doors_state);
		free (cub->p);
		return (1);
	}
	return (-1);
}

int	mymlx_exit(t_cub *cub)
{
	exit(mymlx_destroy(cub));
}
