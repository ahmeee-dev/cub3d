/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:21:02 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/20 09:47:28 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

#define MINIMAP_RIGHT_MARGIN 10
#define MINIMAP_OFFSET_Y 10

#define MINIMAP_CELL_SIZE 25
#define MINIMAP_PLAYER_SIZE 8

#define MINIMAP_WALL_COLOR 0x333333
#define MINIMAP_FLOOR_COLOR 0xFFFFFFFF
#define MINIMAP_PLAYER_COLOR 0xFF0000
#define FOV_FILL_COLOR 0xFFFF00
#define FOV_MAX_RAY_STEPS (MINIMAP_CELL_SIZE * 5)
#define FOV_ANGLE_STEP 0.01f
#define FOV_RADIANS 1.151917f

static void	draw_minimap_square(t_image *img, int start_x, int start_y,
				int size, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if ((start_x + x >= 0 && start_x + x < SCREEN_WIDTH) && \
				(start_y + y >= 0 && start_y + y < SCREEN_HEIGHT))
				mymlx_pixel_put(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	cast_minimap_fov_ray(t_cub *cub, t_2ipoint base_offset, float angle)
{
	t_2fpoint	ray_dir;
	t_2fpoint	curr_pmap;
	t_2ipoint	check;
	int		steps;


	ray_dir = (t_2fpoint){cosf(angle) * 0.03f, sinf(angle) * 0.03f};
	curr_pmap = cub->raycaster.player.pos;
	steps = 0;
	while (steps < FOV_MAX_RAY_STEPS)
	{
		check.x = base_offset.x + (int)(curr_pmap.x * MINIMAP_CELL_SIZE);
		check.y = base_offset.y + (int)(curr_pmap.y * MINIMAP_CELL_SIZE);
		if ((check.x >= 0 && check.x < SCREEN_WIDTH) &&
			(check.y >= 0 && check.y < SCREEN_HEIGHT))
			mymlx_pixel_put(&cub->pic.img, check.x, check.y, FOV_FILL_COLOR);
		if ((int)curr_pmap.x < 0 || (int)curr_pmap.x >= cub->map.sizes.map_lenght ||
			(int)curr_pmap.y < 0 || (int)curr_pmap.y >= cub->map.sizes.map_height)
			break ;
		if (cub->map.matrix[(int)curr_pmap.y * cub->map.sizes.map_lenght + (int)curr_pmap.x] == WALL)
			break ;
		curr_pmap.x += ray_dir.x;
		curr_pmap.y += ray_dir.y;
		steps++;
	}
}

static void	draw_filled_fov(t_cub *cub, t_2ipoint base_offset)
{
	float		player_angle;
	float		fov_half_angle;
	float		start_angle;
	float		end_angle;

	player_angle = atan2f(cub->raycaster.player.dir.y, cub->raycaster.player.dir.x);
	fov_half_angle = FOV_RADIANS / 2.0f;
	start_angle = player_angle - fov_half_angle;
	end_angle = player_angle + fov_half_angle;
	while (start_angle <= end_angle)
	{
		cast_minimap_fov_ray(cub, base_offset, start_angle);
		start_angle += FOV_ANGLE_STEP;
	}
}

void	draw_player_n_fov(t_cub *cub, t_2ipoint screen_pos, int offset_from_x)
{
	screen_pos.x = offset_from_x +
				(int)(cub->raycaster.player.pos.x * MINIMAP_CELL_SIZE);
	screen_pos.y = MINIMAP_OFFSET_Y +
				(int)(cub->raycaster.player.pos.y * MINIMAP_CELL_SIZE);
	draw_minimap_square(&cub->pic.img, screen_pos.x - MINIMAP_PLAYER_SIZE / 2,
						screen_pos.y - MINIMAP_PLAYER_SIZE / 2,
						MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
	draw_filled_fov(cub, (t_2ipoint){offset_from_x, MINIMAP_OFFSET_Y});
}

void	draw_minimap(t_cub *cub)
{
	t_2ipoint		idx;
	t_2ipoint		screen_pos;
	unsigned int	cell_color;
	int				offset_from_x;

	offset_from_x = SCREEN_WIDTH -
						(cub->map.sizes.map_lenght * MINIMAP_CELL_SIZE) -
						MINIMAP_RIGHT_MARGIN;
	idx.y = 0;
	while ((idx.y)++ < cub->map.sizes.map_height)
	{
		idx.x = 0;
		while ((idx.x)++ < cub->map.sizes.map_lenght)
		{
			screen_pos.x = offset_from_x + idx.x * MINIMAP_CELL_SIZE;
			screen_pos.y = MINIMAP_OFFSET_Y + idx.y * MINIMAP_CELL_SIZE;
			if (cub->map.matrix[idx.y * cub->map.sizes.map_lenght + idx.x] == WALL)
				cell_color = MINIMAP_WALL_COLOR;
			else
				cell_color = MINIMAP_FLOOR_COLOR;
			draw_minimap_square(&cub->pic.img, screen_pos.x, screen_pos.y,
								MINIMAP_CELL_SIZE, cell_color);
		}
	}
	draw_player_n_fov(cub, screen_pos, offset_from_x);
}

