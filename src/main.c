/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:06 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 11:50:55 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision(float x, float y)
{
	t_map *map;
	int width = SCREEN_WIDTH / CELL_SIZE;
	int map_x = (int)(x / CELL_SIZE);
	int map_y = (int)(y / CELL_SIZE);

	map = map_get(width, SCREEN_HEIGHT / CELL_SIZE);
	if (!map)
		return (1);
	if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= SCREEN_HEIGHT / CELL_SIZE)
	{
		free(map);
		return (1);
	}
	if (map[map_y * width + map_x].type == 1)
	{
		free(map);
		return (1);
	}
	free(map);
	return (0);
}

int	key_handler(int keycode, t_mlx *data)
{
	float moveSpeed = 5.0f;
	float rotSpeed = 0.1f;
	float newX, newY;

	if (keycode == 53)
		mymlx_exit(data);
	else if (keycode == 13) // W
	{
		newX = data->raycaster.player->pos.x + data->raycaster.player->dir.x * moveSpeed;
		newY = data->raycaster.player->pos.y + data->raycaster.player->dir.y * moveSpeed;
		if (!check_collision(newX, newY))
		{
			data->raycaster.player->pos.x = newX;
			data->raycaster.player->pos.y = newY;
		}
	}
	else if (keycode == 1) // S
	{
		newX = data->raycaster.player->pos.x - data->raycaster.player->dir.x * moveSpeed;
		newY = data->raycaster.player->pos.y - data->raycaster.player->dir.y * moveSpeed;
		if (!check_collision(newX, newY))
		{
			data->raycaster.player->pos.x = newX;
			data->raycaster.player->pos.y = newY;
		}
	}
	else if (keycode == 0) // A
	{
		newX = data->raycaster.player->pos.x + data->raycaster.player->dir.y * moveSpeed;
		newY = data->raycaster.player->pos.y - data->raycaster.player->dir.x * moveSpeed;
		if (!check_collision(newX, newY))
		{
			data->raycaster.player->pos.x = newX;
			data->raycaster.player->pos.y = newY;
		}
	}
	else if (keycode == 2) // D
	{
		newX = data->raycaster.player->pos.x - data->raycaster.player->dir.y * moveSpeed;
		newY = data->raycaster.player->pos.y + data->raycaster.player->dir.x * moveSpeed;
		if (!check_collision(newX, newY))
		{
			data->raycaster.player->pos.x = newX;
			data->raycaster.player->pos.y = newY;
		}
	}
	else if (keycode == 123) //Fercetta sx
	{
		float oldDirX = data->raycaster.player->dir.x;
		data->raycaster.player->dir.x = data->raycaster.player->dir.x * cosf(-rotSpeed) - data->raycaster.player->dir.y * sinf(-rotSpeed);
		data->raycaster.player->dir.y = oldDirX * sinf(-rotSpeed) + data->raycaster.player->dir.y * cosf(-rotSpeed);

		float oldPlaneX = data->raycaster.player->plane.x;
		data->raycaster.player->plane.x = data->raycaster.player->plane.x * cosf(-rotSpeed) - data->raycaster.player->plane.y * sinf(-rotSpeed);
		data->raycaster.player->plane.y = oldPlaneX * sinf(-rotSpeed) + data->raycaster.player->plane.y * cosf(-rotSpeed);
	}
	else if (keycode == 124) //Freccetta dx
	{
		float oldDirX = data->raycaster.player->dir.x;
		data->raycaster.player->dir.x = data->raycaster.player->dir.x * cosf(rotSpeed) - data->raycaster.player->dir.y * sinf(rotSpeed);
		data->raycaster.player->dir.y = oldDirX * sinf(rotSpeed) + data->raycaster.player->dir.y * cosf(rotSpeed);

		float oldPlaneX = data->raycaster.player->plane.x;
		data->raycaster.player->plane.x = data->raycaster.player->plane.x * cosf(rotSpeed) - data->raycaster.player->plane.y * sinf(rotSpeed);
		data->raycaster.player->plane.y = oldPlaneX * sinf(rotSpeed) + data->raycaster.player->plane.y * cosf(rotSpeed);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	data;

	(void)argc;
	if (!map_parsing(argv[1], &data.data))
		ft_printf("Error: Invalid map file\n");
	exit(0);
	mymlx_init(&data, "map.cub");
	mlx_hook(data.pic.win.p, 17, 0, mymlx_exit, &data);
	mlx_key_hook(data.pic.win.p, key_handler, &data);
	mlx_loop_hook(data.mlx_p, mymlx_render, &data);
	mlx_loop(data.mlx_p);

	return (0);
}

