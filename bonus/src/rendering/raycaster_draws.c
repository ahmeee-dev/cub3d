/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_draws.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/20 17:19:45 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player(char c);

void draw_vertical_line(t_image *img, int x, t_2ipoint range, unsigned int color)
{
	int y;
	char *dest;

	if (x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (range.x < 0)
		range.x = 0;
	if (range.y >= SCREEN_HEIGHT)
		range.y = SCREEN_HEIGHT - 1;
	if (range.x > range.y)
		return ;
	dest = img->addr + (range.x * img->lenght + x * (img->bits_pp / 8));
	y = range.x;
	while (y <= range.y)
	{
		*((unsigned int *)dest) = color;
		dest += img->lenght;
		y++;
	}
}

void	draw_texture_line(t_cub *cub, t_ray *ray, t_image *w_texture, int x)
{
	double		wall_x;
	t_2ipoint	tex_pos;
	t_2ipoint	tmp;
	int			tmp_y;
	char		*pixel;
	unsigned int color;

	if (ray->side == 0)
		wall_x = cub->raycaster.player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = cub->raycaster.player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_pos.x = (int)(wall_x * w_texture->size.width);
	if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1 && ray->dir.y < 0))
		tex_pos.x = w_texture->size.width - tex_pos.x - 1;
	tmp_y = ray->draw_start;
	while (tmp_y <= ray->draw_end)
	{
		tmp.x = tmp_y * 256 - SCREEN_HEIGHT * 128 + ray->line_height * 128;
		tex_pos.y = (tmp.x * w_texture->size.height) / ray->line_height / 256;
		if (tex_pos.y >= 0 && tex_pos.y < w_texture->size.height
			&& tex_pos.x >= 0 && tex_pos.x < w_texture->size.width)
		{
			pixel = w_texture->addr + (tex_pos.y * w_texture->lenght
				+ tex_pos.x * (w_texture->bits_pp / 8));
			color = *(unsigned int *)pixel;
			mymlx_pixel_put(&cub->pic.img, x, tmp_y, color);
		}
		tmp_y++;
	}
}

void	draw_column_parts(t_cub *cub, int x, t_ray *ray,
	unsigned int ceiling_color, unsigned int floor_color)
{
	t_image	*w_texture;

	draw_vertical_line(&cub->pic.img, x, (t_2ipoint){0, ray->draw_start - 1}, ceiling_color);
	w_texture = &cub->textures.wall;
	if (w_texture && w_texture->addr)
		draw_texture_line(cub, ray, w_texture, x);
	draw_vertical_line(&cub->pic.img, x, (t_2ipoint){ray->draw_end + 1,
		SCREEN_HEIGHT - 1}, floor_color);
}

void	fill_remaining_columns(t_cub *cub, t_ray *ray, int x,
	unsigned int ceiling_color, unsigned int floor_color)
{
	int	inc;
	int	i;

	if (ray->perp_wall_dist > LOD_THRESHOLD)
		inc = RENDER_SCALE;
	else
		inc = 1;
	if (inc <= 1 || x + inc >= SCREEN_WIDTH)
		return ;
	i = 1;
	while (i < inc && x + i < SCREEN_WIDTH)
	{
		draw_column_parts(cub, x + i, ray, ceiling_color, floor_color);
		i++;
	}
}

