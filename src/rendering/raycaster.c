/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/19 11:28:08 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray_dir(t_ray *ray, t_player *p, float camera)
{
	ray->dir.x = p->dir.x + p->plane.x * camera;
	ray->dir.y = p->dir.y + p->plane.y * camera;
	ray->cell_pos.x = (int)p->pos.x;
	ray->cell_pos.y = (int)p->pos.y;
}

static void	init_delta_dist(t_ray *ray)
{
	if (fabsf(ray->dir.x) < 0.00001f)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabsf(1.0f / ray->dir.x);
	if (fabsf(ray->dir.y) < 0.00001f)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabsf(1.0f / ray->dir.y);
}

static void	init_side_dist(t_ray *ray, t_player *p)
{
	t_2fpoint	pos_diff;

	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		pos_diff.x = p->pos.x - ray->cell_pos.x;
	}
	else
	{
		ray->step.x = 1;
		pos_diff.x = ray->cell_pos.x + 1.0f - p->pos.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		pos_diff.y = p->pos.y - ray->cell_pos.y;
	}
	else
	{
		ray->step.y = 1;
		pos_diff.y = ray->cell_pos.y + 1.0f - p->pos.y;
	}
	ray->side_dist.x = pos_diff.x * ray->delta_dist.x;
	ray->side_dist.y = pos_diff.y * ray->delta_dist.y;
}
void	update_dda_step(t_ray *ray)
{
	int is_x_shorter;

	is_x_shorter = (ray->side_dist.x < ray->side_dist.y);
	ray->side_dist.x += ray->delta_dist.x * (is_x_shorter);
	ray->side_dist.y += ray->delta_dist.y * (!is_x_shorter);
	ray->cell_pos.x += ray->step.x * (is_x_shorter);
	ray->cell_pos.y += ray->step.y * (!is_x_shorter);
	ray->side = !is_x_shorter;
}
static int	execute_dda_step(t_ray *ray, t_map *map)
{
	int		map_index;
	float	distance;

	update_dda_step(ray);
	if (ray->side == 0)
		distance = ray->side_dist.x - ray->delta_dist.x;
	else
		distance = ray->side_dist.y - ray->delta_dist.y;
	if (distance > VIEW_DISTANCE)
	{
		ray->perp_wall_dist = VIEW_DISTANCE;
		return (1);
	}
	if (ray->cell_pos.x < 0 || ray->cell_pos.x >= map->sizes.map_lenght ||
		ray->cell_pos.y < 0 || ray->cell_pos.y >= map->sizes.map_height)
	{
		ray->perp_wall_dist = VIEW_DISTANCE;
		return (1);
	}
	map_index = ray->cell_pos.y * map->sizes.map_lenght + ray->cell_pos.x;
	if (map->matrix[map_index] == WALL)
		return (1);
	return (0);
}

void	update_cast_data(t_ray *ray, t_player *p, float camera)
{
	init_ray_dir(ray, p, camera);
	init_delta_dist(ray);
	init_side_dist(ray, p);
}

void	run_dda_algorithm(t_ray *ray, t_map *map)
{
	int	count;

	count = 0;
	while (count < (int)(VIEW_DISTANCE * 2.0f))
	{
		if (execute_dda_step(ray, map))
			return;
		count++;
	}
	ray->perp_wall_dist = VIEW_DISTANCE;
}

void	cast_ray(t_ray *ray, t_player *p, t_map *map, int x)
{
	float	camera;

	camera = 2 * x / (float)SCREEN_WIDTH - 1;
	update_cast_data(ray, p, camera);
	run_dda_algorithm(ray, map);

	if (ray->side == 0)
		ray->perp_wall_dist = fabsf((ray->cell_pos.x - p->pos.x + (1 - ray->step.x) / 2) / ray->dir.x);
	else
		ray->perp_wall_dist = fabsf((ray->cell_pos.y - p->pos.y + (1 - ray->step.y) / 2) / ray->dir.y);
	if (ray->perp_wall_dist <= 0.1f)
		ray->perp_wall_dist = 0.1f;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (SCREEN_HEIGHT - ray->line_height) / 2;
	ray->draw_end = (SCREEN_HEIGHT + ray->line_height) / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

static int	get_x_increment(float perp_dist)
{
	if (perp_dist > LOD_THRESHOLD)
		return (RENDER_SCALE);
	return (1);
}

static void	draw_textured_column(t_cub *cub, t_ray *ray, int x)
{
	t_image			*texture;
	double			wall_x;
	t_2ipoint		tex_pos;
	t_2ipoint		tmp;
	char			*pixel;
	unsigned int	color;

	if (!cub || !ray)
		return ;
	if (ray->side == 0)
	{
		if (ray->step.x > 0)
			texture = &cub->textures.wall.east;
		else
			texture = &cub->textures.wall.west;
	}
	else
	{
		if (ray->step.y > 0)
			texture = &cub->textures.wall.south;
		else
			texture = &cub->textures.wall.north;
	}
	if (!texture || !texture->addr)
		return ;
	if (ray->side == 0)
		wall_x = cub->raycaster.player.pos.y
			+ ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = cub->raycaster.player.pos.x
			+ ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_pos.x = (int)(wall_x * texture->size.width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_pos.x = texture->size.width - tex_pos.x - 1;
	tmp.y = ray->draw_start;
	while (tmp.y <= ray->draw_end)
	{
		tmp.x = tmp.y * 256 - SCREEN_HEIGHT * 128 + ray->line_height * 128;
		tex_pos.y = (tmp.x * texture->size.height) / ray->line_height / 256;
		if (tex_pos.y < 0 || tex_pos.y >= texture->size.height
			|| tex_pos.x < 0 || tex_pos.x >= texture->size.width)
		{
			(tmp.y)++;
			continue ;
		}
		pixel = texture->addr
			+ (tex_pos.y * texture->lenght + tex_pos.x * (texture->bits_pp / 8));
		color = *(unsigned int *)pixel;
		mymlx_pixel_put(&cub->pic.img, x, (tmp.y), color);
		(tmp.y)++;
	}
}

static void render_column(t_cub *cub, int x,
		unsigned int ceiling_color, unsigned int floor_color)
{
	t_ray *ray;
	int i;
	int inc;

	ray = &cub->raycaster.rays[x];
	draw_vertical_line(&cub->pic.img, x,
		0, ray->draw_start - 1, ceiling_color);
	draw_textured_column(cub, ray, x);
	draw_vertical_line(&cub->pic.img, x,
		ray->draw_end + 1, SCREEN_HEIGHT - 1, floor_color);
	inc = get_x_increment(ray->perp_wall_dist);
	if (inc > 1 && x + inc < SCREEN_WIDTH)
	{
		i = 1;
		while (i < inc && x + i < SCREEN_WIDTH)
		{
			draw_vertical_line(&cub->pic.img, x + i,
				0, ray->draw_start - 1, ceiling_color);
			draw_textured_column(cub, ray, x + i);
			draw_vertical_line(&cub->pic.img, x + i,
				ray->draw_end + 1, SCREEN_HEIGHT - 1, floor_color);
			i++;
		}
	}
}

int	render_scene(t_cub *cub)
{
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	int			x;

	ceiling_color = cub->map.data.ceiling;
	floor_color = cub->map.data.floor;
	ft_bzero(cub->pic.img.addr,
		SCREEN_WIDTH * SCREEN_HEIGHT * (cub->pic.img.bits_pp / 8));
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cast_ray(&cub->raycaster.rays[x],
			&cub->raycaster.player, &cub->map, x);
		render_column(cub, x, ceiling_color, floor_color);
		x += get_x_increment(
			cub->raycaster.rays[x].perp_wall_dist);
	}
	mlx_put_image_to_window(cub->p, cub->pic.win.p,
		cub->pic.img.p, 0, 0);
	update_fps_counter(cub);
	return (0);
}
