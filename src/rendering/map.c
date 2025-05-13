/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:19:36 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 09:21:15 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map	*map_get(int width, int height)
{
	t_map	*tmp_map;

	tmp_map = malloc(sizeof(t_map) * width * height);
	if (!tmp_map)
		return (NULL);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tmp_map[y * width + x].p.x = x * CELL_SIZE;
			tmp_map[y * width + x].p.y = y * CELL_SIZE;
			tmp_map[y * width + x].p.z = 0;

			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
				tmp_map[y * width + x].type = 1; // muro
			else
				tmp_map[y * width + x].type = 0; // spazio vuoto
		}
	}

	//Labirinto
	for (int x = 5; x < width - 5; x += 8) {
		for (int len = 0; len < 5; len++) {
			if (x + len < width - 1)
				tmp_map[5 * width + x + len].type = 1;
		}
	}

	//Parte sinistra del lab
	for (int y = 5; y < height - 5; y += 8) {
		for (int len = 0; len < 5; len++) {
			if (y + len < height - 1)
				tmp_map[(y + len) * width + 5].type = 1;
		}
	}

	if (width > 20 && height > 20) {
		for (int count = 0; count < 10; count++) {
			int rx = 10 + (count * 7) % (width - 20);
			int ry = 10 + (count * 11) % (height - 20);

			//Stanza quadrata temporanea
			for (int dy = 0; dy < 3; dy++) {
				for (int dx = 0; dx < 3; dx++) {
					int px = rx + dx;
					int py = ry + dy;
					if (px > 0 && px < width-1 && py > 0 && py < height-1) {
						if (dx == 0 || dx == 2 || dy == 0 || dy == 2) // Solo i bordi
							tmp_map[py * width + px].type = 1;
					}
				}
			}
		}
	}

	return (tmp_map);
}

void	ray_visual_plot(t_map *map, t_mlx *data)
{
	int width = SCREEN_WIDTH / CELL_SIZE;
	int height = SCREEN_HEIGHT / CELL_SIZE;
	int hit = 0;
	t_2fpoint ray;
	ray.x = data->raycaster.player->pos.x;
	ray.y = data->raycaster.player->pos.y;
	while (!hit)
	{
		ray.x += data->raycaster.player->dir.x;
		ray.y += data->raycaster.player->dir.y;
		int map_x = (int)(ray.x / CELL_SIZE);
		int map_y = (int)(ray.y / CELL_SIZE);
		if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= height)
			break;
		if (map[map_y * width + map_x].type == 1)
			hit = 1;
	}
	t_2fpoint draw;
	draw.x = data->raycaster.player->pos.x;
	draw.y = data->raycaster.player->pos.y;
	while ((int)draw.x != (int)ray.x || (int)draw.y != (int)ray.y)
	{
		mymlx_pixel_put(data, (int)draw.x, (int)draw.y, 0x00FF00);
		draw.x += data->raycaster.player->dir.x;
		draw.y += data->raycaster.player->dir.y;
	}
}

void	map_plot(t_mlx *data)
{
	int		width = SCREEN_WIDTH / CELL_SIZE;
	int		height = SCREEN_HEIGHT / CELL_SIZE;
	int		cell_size = CELL_SIZE;
	t_map	*map = map_get(width, height);

	if (!map)
		return;

	// Disegna la mappa
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			int color = (map[j * width + i].type == 1) ? 0xFFFFFF : 0x555555;
			for (int y = 0; y < cell_size; y++) {
				for (int x = 0; x < cell_size; x++) {
					mymlx_pixel_put(data, i * cell_size + x, j * cell_size + y, color);
				}
			}
		}
	}

	//pointer del player
	int player_x = (int)(data->raycaster.player->pos.x);
	int player_y = (int)(data->raycaster.player->pos.y);
	for (int y = -5; y <= 5; y++)
	{
		for (int x = -5; x <= 5; x++)
		{
			if (x * x + y * y <= 25)
				mymlx_pixel_put(data, player_x + x, player_y + y, 0xFF0000);
		}
	}

	ray_visual_plot(map, data);
	free(map);
}
