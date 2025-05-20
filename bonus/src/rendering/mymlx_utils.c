/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:08 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/20 15:59:42 by apintaur         ###   ########.fr       */
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
		ft_printf("Error: cannot load xpm!\n");
		mymlx_exit(cub);
	}
	img->addr = mlx_get_data_addr(img->p, &img->bits_pp, \
		&img->lenght, &img->endian);
}

static void	load_textures(t_cub *cub)
{
	load_single_texture(cub, &cub->textures.wall, cub->map.data.wall);
	load_single_texture(cub, &cub->textures.gun1, cub->map.data.gun1);
	load_single_texture(cub, &cub->textures.gun2, cub->map.data.gun2);
	load_single_texture(cub, &cub->textures.door, cub->map.data.door);
	load_single_texture(cub, &cub->textures.ceiling1, cub->map.data.ceiling1);
	load_single_texture(cub, &cub->textures.ceiling2, cub->map.data.ceiling2);
	load_single_texture(cub, &cub->textures.ceiling3, cub->map.data.ceiling3);
	load_single_texture(cub, &cub->textures.hand, cub->map.data.hand);
	load_single_texture(cub, &cub->textures.floor1, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor2, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor3, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor4, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor5, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor6, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor7, cub->map.data.floor1);
	load_single_texture(cub, &cub->textures.floor8, cub->map.data.floor1);
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
		mlx_destroy_image(cub->p, cub->textures.gun1.p);
		mlx_destroy_image(cub->p, cub->textures.gun2.p);
		mlx_destroy_image(cub->p, cub->textures.ceiling1.p);
		mlx_destroy_image(cub->p, cub->textures.ceiling2.p);
		mlx_destroy_image(cub->p, cub->textures.ceiling3.p);
		mlx_destroy_image(cub->p, cub->textures.floor1.p);
		mlx_destroy_image(cub->p, cub->textures.floor2.p);
		mlx_destroy_image(cub->p, cub->textures.floor3.p);
		mlx_destroy_image(cub->p, cub->textures.floor4.p);
		mlx_destroy_image(cub->p, cub->textures.floor5.p);
		mlx_destroy_image(cub->p, cub->textures.floor6.p);
		mlx_destroy_image(cub->p, cub->textures.floor7.p);
		mlx_destroy_image(cub->p, cub->textures.floor8.p);
		mlx_destroy_window(cub->p, cub->pic.win.p);
		free (cub->raycaster.rays);
		free (cub->p);
		return (1);
	}
	return (-1);
}
