/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 08:38:15 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ray_forword_check(t_ray *ray, t_player *p)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (p->pos.x - ray->cell_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->cell_pos.x + 1.0 - p->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (p->pos.y - ray->cell_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->cell_pos.y + 1.0 - p->pos.y) * ray->delta_dist.y;
	}
}

void	update_cast_data(t_ray *ray, t_player *p, float camera)
{
	ray->dir.x = p->dir.x + p->plane.x * camera;
	ray->dir.y = p->dir.y + p->plane.y * camera;
	ray->cell_pos = (t_2ipoint){(int)p->pos.x, (int)p->pos.y};
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray_forword_check(ray, p);
}

void	run_dda_algorithm(t_ray *ray, t_map *map)
{
	int	hit;
	int map_index;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->cell_pos.x += ray->step.x;
			ray->side = 0; // ha colpito lato verticale
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->cell_pos.y += ray->step.y;
			ray->side = 1; // ha colpito lato orizzontale
		}

		if (ray->cell_pos.x < 0 || ray->cell_pos.x >= map->sizes.map_lenght ||
			ray->cell_pos.y < 0 || ray->cell_pos.y >= map->sizes.map_height)
			hit = 1;
		else
		{
			map_index = ray->cell_pos.y * map->sizes.map_lenght + ray->cell_pos.x;
			if (map_index >= 0 && map_index < (map->sizes.map_height * map->sizes.map_lenght))
			{
				if (map->matrix[map_index] == WALL)
					hit = 1;
			}
			else
				hit = 1;
		}
	}
}

void	cast_ray(t_ray *ray, t_player *p, t_map *map, int x)
{
	float	camera;

	camera = 2 * x / (float)SCREEN_WIDTH - 1;
	update_cast_data(ray, p, camera);
	run_dda_algorithm(ray, map);
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->cell_pos.x - p->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->cell_pos.y - p->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;

	if (ray->perp_wall_dist <= 0.1f)
		ray->perp_wall_dist = 0.1f;

	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;

	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

int	render_scene(t_cub *cub)
{
	t_2ipoint	idx;
	unsigned int wall_color;

	idx.x = 0;
	while (idx.x < SCREEN_WIDTH)
	{
		cast_ray(&cub->raycaster.rays[idx.x], &cub->raycaster.player, &cub->map, idx.x);

		//Cielo
		idx.y = 0;
		while (idx.y < cub->raycaster.rays[idx.x].draw_start)
		{
			mymlx_pixel_put(&cub->pic.img, idx.x, idx.y, cub->map.data.ceiling);
			idx.y++;
		}

		//Muro
		idx.y = cub->raycaster.rays[idx.x].draw_start;
		// Sfumatura basata sulla distanza per dare profondità
		if (cub->raycaster.rays[idx.x].side == 1)
			wall_color = 0x888888;
		else
			wall_color = 0xCCCCCC;

		if (cub->raycaster.rays[idx.x].perp_wall_dist > 5)
			wall_color = darken_color(wall_color, cub->raycaster.rays[idx.x].perp_wall_dist);

		while (idx.y <= cub->raycaster.rays[idx.x].draw_end)
		{
			mymlx_pixel_put(&cub->pic.img, idx.x, idx.y, wall_color);
			idx.y++;
		}

		//Pavimento
		idx.y = cub->raycaster.rays[idx.x].draw_end + 1;
		while (idx.y < SCREEN_HEIGHT)
		{
			mymlx_pixel_put(&cub->pic.img, idx.x, idx.y, cub->map.data.floor);
			idx.y++;
		}
		idx.x++;
	}
	mlx_put_image_to_window(cub->p, cub->pic.win.p, cub->pic.img.p, 0, 0);
	return (0);
}
