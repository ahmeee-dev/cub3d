/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:08 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/21 15:36:13 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>

void	load_single_texture(t_cub *cub, t_image *img, char *path)
{
	img->p = mlx_xpm_file_to_image(cub->p, path, \
		&img->size.width, &img->size.height);
	if (!img->p)
	{
		ft_printf("%s Error: cannot load xpm!\n", path);
		mymlx_exit(cub);
	}
	img->addr = mlx_get_data_addr(img->p, &img->bits_pp, \
		&img->lenght, &img->endian);
}

static void	load_textures(t_cub *cub)
{
	load_single_texture(cub, &cub->textures.wall, cub->map.data.wall);
	load_single_texture(cub, &cub->textures.gun_fire, cub->map.data.gun1);
	load_single_texture(cub, &cub->textures.gun_nofire, cub->map.data.gun2);
	load_single_texture(cub, &cub->textures.door, cub->map.data.door);
	load_single_texture(cub, &cub->textures.ceiling_light, cub->map.data.ceiling1);
	load_single_texture(cub, &cub->textures.ceiling_nolight, cub->map.data.ceiling2);
	load_single_texture(cub, &cub->textures.hand, cub->map.data.hand);
	load_single_texture(cub, &cub->textures.floor_light, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor_nolight, cub->map.data.floor2);
}

void	mymlx_init(t_cub *cub, char *argv[])
{
	if (!map_parsing(argv[1], &cub->map))
	{
		ft_printf("Error: Invalid map file\n");
		exit (EXIT_FAILURE);
	}
	cub->p = NULL;
	cub->pic.img.p = NULL;
	cub->pic.win.p = NULL;
	cub->p = mlx_init();
	if (!cub->p)
		exit(EXIT_FAILURE);
	cub->pic.win.p = mlx_new_window(cub->p, SCREEN_WIDTH,
		SCREEN_HEIGHT, "Cub3d");
	cub->pic.img.p = mlx_new_image(cub->p, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->pic.img.addr = mlx_get_data_addr(cub->pic.img.p, &cub->pic.img.bits_pp, \
							&cub->pic.img.lenght, &cub->pic.img.endian);
	cub->pic.img.size.width = SCREEN_WIDTH;
	cub->pic.img.size.height = SCREEN_HEIGHT;
	cub->mouse_times = 0;
	cub->mouse_x = 0;
	cub->keys = (t_keys){0, 0, 0, 0, 0, 0};
	load_textures(cub);
	raycaster_init(cub);
	init_fps_counter(cub);
	mlx_do_key_autorepeaton(cub->p);
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
		free (cub->p);
		return (1);
	}
	return (-1);
}
