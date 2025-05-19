/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 19:59:10 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player(char c);

void	init_dir_n_plane(char type, t_player *player)
{
	if (type == 'N')
	{
		player->dir = (t_2fpoint){0.0f, -1.0f};
		player->plane = (t_2fpoint){0.66f, 0.0f};
	}
	else if (type == 'S')
	{
		player->dir = (t_2fpoint){0.0f, 1.0f};
		player->plane = (t_2fpoint){-0.66f, 0.0f};
	}
	else if (type == 'E')
	{
		player->dir = (t_2fpoint){1.0f, 0.0f};
		player->plane = (t_2fpoint){0.0f, 0.66f};
	}
	else if (type == 'W')
	{
		player->dir = (t_2fpoint){-1.0f, 0.0f};
		player->plane = (t_2fpoint){0.0f, -0.66f};
	}
}

void draw_vertical_line(t_image *img, int x, int y_start, int y_end, unsigned int color)
{
	int y;
	char *dest;

	if (x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (y_start < 0)
		y_start = 0;
	if (y_end >= SCREEN_HEIGHT)
		y_end = SCREEN_HEIGHT - 1;
	if (y_start > y_end)
		return ;
	dest = img->addr + (y_start * img->lenght + x * (img->bits_pp / 8));
	y = y_start;
	while (y <= y_end)
	{
		*((unsigned int *)dest) = color;
		dest += img->lenght;
		y++;
	}
}

void draw_horizontal_line(t_image *img, int y, int x_start, int x_end, unsigned int color)
{
	int x;
	char *dest;

	if (y < 0 || y >= SCREEN_HEIGHT)
		return;
	if (x_start < 0)
		x_start = 0;
	if (x_end >= SCREEN_WIDTH)
		x_end = SCREEN_WIDTH - 1;
	if (x_start > x_end)
		return;
	dest = img->addr + (y * img->lenght + x_start * (img->bits_pp / 8));
	x = x_start;
	while (x_start <= x_end)
	{
		*((unsigned int *)dest) = color;
		dest += (img->bits_pp / 8);
		x++;
	}
}

void	fill_rectangle(t_image *img, int x, int y, int width, int height, unsigned int color)
{
	int i;

	if (x < 0)
	{
		width += x;
		x = 0;
	}
	if (y < 0)
	{
		height += y;
		y = 0;
	}
	if (x + width > SCREEN_WIDTH)
			width = SCREEN_WIDTH - x;
	if (y + height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT - y;
	if (width <= 0 || height <= 0)
		return ;
	i = 0;
	while (i < height)
	{
		draw_horizontal_line(img, y + i, x, x + width - 1, color);
		i++;
	}
}

void	raycaster_init(t_cub *cub)
{
	t_2ipoint	idx;
	t_sizes		size;
	char		player_char;

	cub->raycaster.rays = (t_ray *) malloc(sizeof(t_ray) * SCREEN_WIDTH);
	if (!cub->raycaster.rays)
		exit (mymlx_destroy(cub));
	size = cub->map.sizes;
	idx = (t_2ipoint) {0,0};
	while (idx.y < size.map_height)
	{
		idx.x = 0;
		while (idx.x < size.map_lenght)
		{
			if (is_player(cub->map.matrix[idx.y * size.map_lenght + idx.x]))
			{
				player_char = (char)cub->map.matrix[idx.y * size.map_lenght + idx.x];
				cub->raycaster.player.pos.x = idx.x + 0.5f;
				cub->raycaster.player.pos.y = idx.y + 0.5f;
				init_dir_n_plane(player_char, &cub->raycaster.player);
				cub->map.matrix[idx.y * size.map_lenght + idx.x] = FLOOR;
				return ;
			}
			idx.x++;
		}
		idx.y++;
	}
}

