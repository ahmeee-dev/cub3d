/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:01 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 19:52:09 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

# define LEFT 0
# define RIGHT 1

void	check_collisions(t_cub *cub, t_2fpoint new_pos, t_2fpoint old_pos);

void	update_dir(t_cub *cub, int type)
{
	float	old_dir;
	float	old_plane;
	t_2fpoint	*dir;
	t_2fpoint	*plane;

	old_dir = cub->raycaster.player.dir.x;
	old_plane = cub->raycaster.player.plane.x;
	dir = &cub->raycaster.player.dir;
	plane = &cub->raycaster.player.plane;
	if (type == LEFT)
	{
		dir->x = dir->x * cos(-ROTATION_SPEED) - dir->y * sin(-ROTATION_SPEED);
		dir->y = old_dir * sin(-ROTATION_SPEED) + dir->y * cos(-ROTATION_SPEED);
		plane->x = plane->x * cos(-ROTATION_SPEED) - plane->y * sin(-ROTATION_SPEED);
		plane->y = old_plane * sin(-ROTATION_SPEED) + plane->y * cos(-ROTATION_SPEED);
	}
	else if (type == RIGHT)
	{
		dir->x = dir->x * cos(ROTATION_SPEED) - dir->y * sin(ROTATION_SPEED);
		dir->y = old_dir * sin(ROTATION_SPEED) + dir->y * cos(ROTATION_SPEED);
		plane->x = plane->x * cos(ROTATION_SPEED) - plane->y * sin(ROTATION_SPEED);
		plane->y = old_plane * sin(ROTATION_SPEED) + plane->y * cos(ROTATION_SPEED);
	}
}

int	key_hook(int keycode, t_cub *cub)
{
	t_2fpoint	new_pos;

	new_pos = cub->raycaster.player.pos;
	if (keycode == XK_w)
	{
		new_pos.x += cub->raycaster.player.dir.x * MOVE_SPEED;
		new_pos.y += cub->raycaster.player.dir.y * MOVE_SPEED;
	}
	else if (keycode == XK_s)
	{
		new_pos.x -= cub->raycaster.player.dir.x * MOVE_SPEED;
		new_pos.y -= cub->raycaster.player.dir.y * MOVE_SPEED;
	}
	else if (keycode == XK_a)
	{
		new_pos.x -= cub->raycaster.player.plane.x * MOVE_SPEED;
		new_pos.y -= cub->raycaster.player.plane.y * MOVE_SPEED;
		update_dir(cub, LEFT);
	}
	else if (keycode == XK_d)
	{
		new_pos.x += cub->raycaster.player.plane.x * MOVE_SPEED;
		new_pos.y += cub->raycaster.player.plane.y * MOVE_SPEED;
		update_dir(cub, RIGHT);
	}
	else if (keycode == XK_Escape)
		exit(mymlx_destroy(cub));
	check_collisions(cub, new_pos, cub->raycaster.player.pos);
	return (0);
}


int	mymlx_render(t_cub *cub)
{
	ft_bzero(cub->pic.img.addr, SCREEN_WIDTH * SCREEN_HEIGHT * \
			(cub->pic.img.bits_pp / 8));
	// minimap_plot(cub);
	mlx_put_image_to_window(cub->p, cub->pic.win.p, \
							cub->pic.img.p, 0, 0);
	return (0);
}

int	mymlx_exit(t_cub *cub)
{
	exit(mymlx_destroy(cub));
}


void	mymlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*tmp_addr;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		tmp_addr = img->addr + (y * img->lenght \
			+ x * (img->bits_pp / 8));
		*((unsigned int *)tmp_addr) = color;
	}
}



