/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:08 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/21 09:38:59 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>

void	load_texture(t_cub *cub, t_image *img, char *path)
{
	img->p = mlx_xpm_file_to_image(cub->p, path, &img->size.width, &img->size.height);
	ft_printf("%s Error: cannot load xpm!\n", path);
	if (!img->p)
	{
		mymlx_exit(cub);
	}
	img->addr = mlx_get_data_addr(img->p, &img->bits_pp, &img->lenght, &img->endian);
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
	cub->pic.win.p = mlx_new_window(cub->p, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	cub->pic.img.p = mlx_new_image(cub->p, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->pic.img.addr = mlx_get_data_addr(cub->pic.img.p, &cub->pic.img.bits_pp,
						&cub->pic.img.lenght, &cub->pic.img.endian);
	cub->pic.img.size.width = SCREEN_WIDTH;
	cub->pic.img.size.height = SCREEN_HEIGHT;

	load_texture(cub, &cub->textures.wall.north, cub->map.data.nt);
	load_texture(cub, &cub->textures.wall.south, cub->map.data.st);
	load_texture(cub, &cub->textures.wall.east, cub->map.data.et);
	load_texture(cub, &cub->textures.wall.west, cub->map.data.wt);

	cub->keys = (t_keys){0, 0, 0, 0, 0, 0};

	raycaster_init(cub);
	mlx_do_key_autorepeaton(cub->p);
}

int	mymlx_destroy(t_cub *cub)
{
	if (cub)
	{
		mlx_destroy_image(cub->p, cub->pic.img.p);
		mlx_destroy_image(cub->p, cub->textures.wall.east.p);
		mlx_destroy_image(cub->p, cub->textures.wall.west.p);
		mlx_destroy_image(cub->p, cub->textures.wall.south.p);
		mlx_destroy_image(cub->p, cub->textures.wall.north.p);
		mlx_destroy_window(cub->p, cub->pic.win.p);
		free (cub->raycaster.rays);
		free (cub->p);
		return (1);
	}
	return (-1);
}


int	is_valid_position(t_cub *cub, t_2ipoint pos)
{
	int map_index;

	if (pos.x < 0 || pos.x >= cub->map.sizes.map_lenght ||
		pos.y < 0 || pos.y >= cub->map.sizes.map_height)
		return (0);
	map_index = pos.y * cub->map.sizes.map_lenght + pos.x;
	if (map_index < 0 || map_index >= (cub->map.sizes.map_height * cub->map.sizes.map_lenght))
		return (0);
	return (cub->map.matrix[map_index] != WALL);
}

static int	close_x(t_cub *cub, t_2fpoint pos)
{
	t_2ipoint	map_pos;
	float		frac;
	int			next_pos;
	int			next_index;
	float		wall_margin;

	map_pos.x = (int)pos.x;		map_pos.y = (int)pos.y;
		wall_margin = 0.1f;
		frac = pos.x - map_pos.x;
	if (frac < wall_margin || frac > (1.0f - wall_margin))
	{
		next_pos = (frac < wall_margin) ? map_pos.x - 1 : map_pos.x + 1;
		if (next_pos >= 0 && next_pos < cub->map.sizes.map_lenght)
		{
			next_index = map_pos.y * cub->map.sizes.map_lenght
				+ next_pos;
			if (next_index >= 0 && next_index < cub->map.sizes.map_height
				* cub->map.sizes.map_lenght && cub->map.matrix[next_index] == WALL)
				return (1);
		}
	}
	return (0);
}

static int	close_y(t_cub *cub, t_2fpoint pos)
{
	t_2ipoint	map_pos;
	float		frac;
	int			next_pos;
	int			next_index;
	float		wall_margin;

	map_pos.x = (int)pos.x;		map_pos.y = (int)pos.y;
		wall_margin = 0.1f;
		frac = pos.y - map_pos.y;
	if (frac < wall_margin || frac > (1.0f - wall_margin))
	{
		next_pos = (frac < wall_margin) ? map_pos.y - 1 : map_pos.y + 1;
		if (next_pos >= 0 && next_pos < cub->map.sizes.map_height)
		{
			next_index = next_pos * cub->map.sizes.map_lenght
				+ map_pos.x;
			if (next_index >= 0 && next_index < cub->map.sizes.map_height
				* cub->map.sizes.map_lenght && cub->map.matrix[next_index] == WALL)
				return (1);
		}
	}
	return (0);
}

int	is_too_close_to_wall(t_cub *cub, t_2fpoint pos, int axis)
{
	if (axis == 0)
		return (close_x(cub, pos));
	return (close_y(cub, pos));
}

void	check_collisions(t_cub *cub, t_2fpoint new_pos, t_2fpoint old_pos)
{
	t_2ipoint	check_pos_x;
	t_2ipoint	check_pos_y;

	check_pos_x.x = (int)new_pos.x;
	check_pos_x.y = (int)old_pos.y;

	if (is_valid_position(cub, check_pos_x) && !is_too_close_to_wall(cub,
		(t_2fpoint){new_pos.x, old_pos.y}, 0))
		cub->raycaster.player.pos.x = new_pos.x;

	check_pos_y.x = (int)cub->raycaster.player.pos.x;
	check_pos_y.y = (int)new_pos.y;

	if (is_valid_position(cub, check_pos_y) && !is_too_close_to_wall(cub,
		(t_2fpoint){cub->raycaster.player.pos.x, new_pos.y}, 1))
		cub->raycaster.player.pos.y = new_pos.y;
}
