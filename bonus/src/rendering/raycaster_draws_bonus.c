/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_draws_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/21 16:33:55 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player(char c);

// void draw_line(t_image *img, int x, t_2ipoint range, unsigned int color)
// {
// 	int y;
// 	char *dest;

// 	if (x < 0 || x >= SCREEN_WIDTH)
// 		return ;
// 	if (range.x < 0)
// 		range.x = 0;
// 	if (range.y >= SCREEN_HEIGHT)
// 		range.y = SCREEN_HEIGHT - 1;
// 	if (range.x > range.y)
// 		return ;
// 	dest = img->addr + (range.x * img->lenght + x * (img->bits_pp / 8));
// 	y = range.x;
// 	while (y <= range.y)
// 	{
// 		*((unsigned int *)dest) = color;
// 		dest += img->lenght;
// 		y++;
// 	}
// }

unsigned int	dark_filter(unsigned int color, float factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((unsigned int)r << 16) | ((unsigned int)g << 8) | b;
}

void draw_ceiling(t_cub *cub, t_ray *ray, t_image *texture, int x)
{
	int			y;
	int			y_offset;
	float		third_distance;
	t_2ipoint	tx_pos;
	t_2fpoint	floor;

	y = 0;
	while (y < ray->draw_start)
	{
		y_offset = y - SCREEN_HEIGHT / 2;
		third_distance = (0.5 * SCREEN_HEIGHT) / y_offset;
		floor.x = cub->raycaster.player.pos.x - third_distance * ray->dir.x;
		floor.y = cub->raycaster.player.pos.y - third_distance * ray->dir.y;
		tx_pos.x = (int) (floor.x * CELL_SIZE) % texture->size.width;
		tx_pos.y = (int) (floor.y * CELL_SIZE) % texture->size.height;
		if (tx_pos.y >= 0 && tx_pos.y < texture->size.height
			&& tx_pos.x >= 0 && tx_pos.x < texture->size.width)
		{
			unsigned int col;
			col = *(unsigned int *)(texture->addr
			+ (tx_pos.y * texture->lenght + tx_pos.x * (texture->bits_pp / 8)));
			mymlx_pixel_put(&cub->pic.img, x, y, dark_filter(col, 0.4f));
		}
		y++;
	}
}

void		draw_floor(t_cub *cub, t_ray *ray, t_image *texture, int x)
{
	int			y;
	int			y_offset;
	float		third_distance;
	t_2ipoint	tx_pos;
	t_2fpoint	floor;

	y = ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		y_offset = y - SCREEN_HEIGHT / 2;
		third_distance = (0.5 * SCREEN_HEIGHT) / y_offset;
		floor.x = cub->raycaster.player.pos.x + third_distance * ray->dir.x;
		floor.y = cub->raycaster.player.pos.y + third_distance * ray->dir.y;
		tx_pos.x = (int)(floor.x * CELL_SIZE) % texture->size.width;
		tx_pos.y = (int)(floor.y * CELL_SIZE) % texture->size.height;
		if (tx_pos.y >= 0 && tx_pos.y < texture->size.height
			&& tx_pos.x >= 0 && tx_pos.x < texture->size.width)
		{
			unsigned int col;
			col = *(unsigned int *)(texture->addr
		+ (tx_pos.y * texture->lenght + tx_pos.x * (texture->bits_pp / 8)));
			mymlx_pixel_put(&cub->pic.img, x, y, dark_filter(col, 0.6f));
		}
		y++;
	}
}

void		draw_wall(t_cub *cub, t_ray *ray, t_image *tx, int x)
{
	int				y;
	double		wall_x;
	t_2ipoint	tx_pos;
	double		step;
	double		tex_pos;
	unsigned int	color;

	if (ray->side == 0)
		wall_x = cub->raycaster.player.pos.y
			+ ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = cub->raycaster.player.pos.x
			+ ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tx_pos.x = (int)(wall_x * tx->size.width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tx_pos.x = tx->size.width - tx_pos.x - 1;
	step = (double)tx->size.height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2
		+ ray->line_height / 2) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	y = ray->draw_start;
	if (y < 0)
		y = 0;
	while (y <= ray->draw_end && y < SCREEN_HEIGHT)
	{
		tx_pos.y = (int)tex_pos & (tx->size.height - 1);
		tex_pos += step;
		color = *(unsigned int *)(tx->addr
			+ (tx_pos.y * tx->lenght
			+ tx_pos.x * (tx->bits_pp / 8)));
		mymlx_pixel_put(&cub->pic.img, x, y, dark_filter(color, 0.6f));
		y++;
	}
}

void	render_textures(t_cub *cub, int x, t_ray *ray)
{
	t_image	*texture;

	if (x < 0 || x >= SCREEN_WIDTH)
		return;
	texture = &cub->textures.ceiling_nolight;
	if (texture && texture->addr && texture->p)
		draw_ceiling(cub, ray, texture, x);
	texture = &cub->textures.wall;
	if (texture && texture->addr && texture->p) {
		draw_wall(cub, ray, texture, x);
	}
	texture = &cub->textures.floor_nolight;
	if (texture && texture->addr && texture->p)
		draw_floor(cub, ray, texture, x);
}


