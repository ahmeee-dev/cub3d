/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:11 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 08:38:12 by apintaur         ###   ########.fr       */
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
				return;
			}
			idx.x++;
		}
		idx.y++;
	}
}

