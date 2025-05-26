/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:12:51 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/26 16:13:18 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys.w = 1;
	else if (keycode == XK_s)
		cub->keys.s = 1;
	else if (keycode == XK_a)
		cub->keys.a = 1;
	else if (keycode == XK_d)
		cub->keys.d = 1;
	else if (keycode == XK_space)
		cub->keys.space = 1;
	else if (keycode == XK_f)
		cub->keys.f = 1;
	else if (keycode == XK_Escape)
		exit (mymlx_exit(cub));
	return (1);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys.w = 0;
	else if (keycode == XK_s)
		cub->keys.s = 0;
	else if (keycode == XK_a)
		cub->keys.a = 0;
	else if (keycode == XK_d)
		cub->keys.d = 0;
	else if (keycode == XK_space)
		cub->keys.space = 0;
	else if (keycode == XK_f)
	{
		cub->keys.f = 0;
		toggle_door(cub);
	}
	else if (keycode == XK_Escape)
		exit (mymlx_exit(cub));
	return (1);
}

void	key_handler(t_cub *cub)
{
	t_2fpoint		new_pos;

	new_pos = cub->raycaster.player.pos;
	if (cub->keys.w)
	{
		new_pos.x += cub->raycaster.player.dir.x * MOVE_SPEED;
		new_pos.y += cub->raycaster.player.dir.y * MOVE_SPEED;
	}
	if (cub->keys.s)
	{
		new_pos.x -= cub->raycaster.player.dir.x * MOVE_SPEED;
		new_pos.y -= cub->raycaster.player.dir.y * MOVE_SPEED;
	}
	if (cub->keys.a)
		update_dir(cub, LEFT);
	if (cub->keys.d)
		update_dir(cub, RIGHT);
	check_collisions(cub, new_pos, cub->raycaster.player.pos);
}
