/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:01 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/20 16:02:16 by apintaur         ###   ########.fr       */
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
		dir->x = dir->x * cos(-ROT_SPD) - dir->y * sin(-ROT_SPD);
		dir->y = old_dir * sin(-ROT_SPD) + dir->y * cos(-ROT_SPD);
		plane->x = plane->x * cos(-ROT_SPD) - plane->y * sin(-ROT_SPD);
		plane->y = old_plane * sin(-ROT_SPD) + plane->y * cos(-ROT_SPD);
	}
	else if (type == RIGHT)
	{
		dir->x = dir->x * cos(ROT_SPD) - dir->y * sin(ROT_SPD);
		dir->y = old_dir * sin(ROT_SPD) + dir->y * cos(ROT_SPD);
		plane->x = plane->x * cos(ROT_SPD) - plane->y * sin(ROT_SPD);
		plane->y = old_plane * sin(ROT_SPD) + plane->y * cos(ROT_SPD);
	}
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys.w = 1;
	else if (keycode == XK_s)
		cub->keys.s = 1;
	else if (keycode == XK_a)
	{
		cub->keys.a = 1;
		cub->keys.left = 1;
	}
	else if (keycode == XK_d)
	{
		cub->keys.d = 1;
		cub->keys.right = 1;
	}
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
	{
		cub->keys.a = 0;
		cub->keys.left = 0;
	}
	else if (keycode == XK_d)
	{
		cub->keys.d = 0;
		cub->keys.right = 0;
	}
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
	{
		// new_pos.x -= cub->raycaster.player.plane.x * MOVE_SPEED;
		// new_pos.y -= cub->raycaster.player.plane.y * MOVE_SPEED;
	}
	if (cub->keys.d)
	{
		// new_pos.x += cub->raycaster.player.plane.x * MOVE_SPEED;
		// new_pos.y += cub->raycaster.player.plane.y * MOVE_SPEED;
	}
	if (cub->keys.left)
		update_dir(cub, LEFT);
	if (cub->keys.right)
		update_dir(cub, RIGHT);
	check_collisions(cub, new_pos, cub->raycaster.player.pos);
}


int	mymlx_render(t_cub *cub)
{
	ft_bzero(cub->pic.img.addr, SCREEN_WIDTH * SCREEN_HEIGHT * \
			(cub->pic.img.bits_pp / 8));
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



