/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:01 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 08:38:56 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

# define LEFT 0
# define RIGHT 1

void	update_dir(t_cub *cub, int type)
{
	float	old_dir;
	float	old_plane;
	float	rotation_speed;

	rotation_speed = 0.05f;

	old_dir = cub->raycaster.player.dir.x;
	old_plane = cub->raycaster.player.plane.x;
	if (type == LEFT)
	{
		cub->raycaster.player.dir.x = cub->raycaster.player.dir.x * cos(-rotation_speed) -
			cub->raycaster.player.dir.y * sin(-rotation_speed);
		cub->raycaster.player.dir.y = old_dir * sin(-rotation_speed) +
			cub->raycaster.player.dir.y * cos(-rotation_speed);
		cub->raycaster.player.plane.x = cub->raycaster.player.plane.x * cos(-rotation_speed) -
			cub->raycaster.player.plane.y * sin(-rotation_speed);
		cub->raycaster.player.plane.y = old_plane * sin(-rotation_speed) +
			cub->raycaster.player.plane.y * cos(-rotation_speed);
	}
	else if (type == RIGHT)
	{
		cub->raycaster.player.dir.x = cub->raycaster.player.dir.x * cos(rotation_speed) -
			cub->raycaster.player.dir.y * sin(rotation_speed);
		cub->raycaster.player.dir.y = old_dir * sin(rotation_speed) +
			cub->raycaster.player.dir.y * cos(rotation_speed);
		cub->raycaster.player.plane.x = cub->raycaster.player.plane.x * cos(rotation_speed) -
			cub->raycaster.player.plane.y * sin(rotation_speed);
		cub->raycaster.player.plane.y = old_plane * sin(rotation_speed) +
			cub->raycaster.player.plane.y * cos(rotation_speed);
	}
}


int	is_valid_position(t_cub *cub, t_2ipoint pos)
{
	int map_index;

	if (pos.x < 0 || pos.x >= cub->map.sizes.map_lenght ||
		pos.y < 0 || pos.y >= cub->map.sizes.map_height)
		return (0);

	map_index = pos.y * cub->map.sizes.map_lenght + pos.x;
	if (map_index < 0 || map_index >= (cub->map.sizes.map_height * cub->map.sizes.map_lenght))
		return (0);

	return (cub->map.matrix[map_index] != WALL);
}

int	is_too_close_to_wall(t_cub *cub, t_2fpoint pos, int axis)
{
	float		wall_margin;
	float		frac;
	t_2ipoint	map_pos;
	int			next_pos;
	int			next_index;

	wall_margin = 0.3f;
	map_pos.x = (int)pos.x;
	map_pos.y = (int)pos.y;

	if (axis == 0) //asse x
	{
		frac = pos.x - map_pos.x;
		if (frac < wall_margin || frac > (1.0f - wall_margin))
		{
			next_pos = (frac < wall_margin) ? map_pos.x - 1 : map_pos.x + 1;
			if (next_pos >= 0 && next_pos < cub->map.sizes.map_lenght)
			{
				next_index = map_pos.y * cub->map.sizes.map_lenght + next_pos;
				if (next_index >= 0 && next_index < (cub->map.sizes.map_height * cub->map.sizes.map_lenght) &&
					cub->map.matrix[next_index] == WALL)
					return (1);
			}
		}
	}
	else // asse Y
	{
		frac = pos.y - map_pos.y;
		if (frac < wall_margin || frac > (1.0f - wall_margin))
		{
			next_pos = (frac < wall_margin) ? map_pos.y - 1 : map_pos.y + 1;
			if (next_pos >= 0 && next_pos < cub->map.sizes.map_height)
			{
				next_index = next_pos * cub->map.sizes.map_lenght + map_pos.x;
				if (next_index >= 0 && next_index < (cub->map.sizes.map_height * cub->map.sizes.map_lenght) &&
					cub->map.matrix[next_index] == WALL)
					return (1);
			}
		}
	}

	return (0);
}


void	check_collisions(t_cub *cub, t_2fpoint new_pos, t_2fpoint old_pos)
{
	t_2ipoint	check_pos_x;
	t_2ipoint	check_pos_y;

	check_pos_x.x = (int)new_pos.x;
	check_pos_x.y = (int)old_pos.y;

	if (is_valid_position(cub, check_pos_x) && !is_too_close_to_wall(cub,
		(t_2fpoint){new_pos.x, old_pos.y}, 0))
		cub->raycaster.player.pos.x = new_pos.x;

	check_pos_y.x = (int)cub->raycaster.player.pos.x;
	check_pos_y.y = (int)new_pos.y;

	if (is_valid_position(cub, check_pos_y) && !is_too_close_to_wall(cub,
		(t_2fpoint){cub->raycaster.player.pos.x, new_pos.y}, 1))
		cub->raycaster.player.pos.y = new_pos.y;
}


int	key_hook(int keycode, t_cub *cub)
{
	t_2fpoint	old_pos;
	t_2fpoint	new_pos;
	float		move_speed;

	move_speed = 0.1f;
	old_pos = cub->raycaster.player.pos;
	new_pos = old_pos;

	if (keycode == XK_w)
	{
		new_pos.x += cub->raycaster.player.dir.x * move_speed;
		new_pos.y += cub->raycaster.player.dir.y * move_speed;
	}
	else if (keycode == XK_s)
	{
		new_pos.x -= cub->raycaster.player.dir.x * move_speed;
		new_pos.y -= cub->raycaster.player.dir.y * move_speed;
	}
	else if (keycode == XK_a)
	{
		new_pos.x -= cub->raycaster.player.plane.x * move_speed;
		new_pos.y -= cub->raycaster.player.plane.y * move_speed;
		update_dir(cub, LEFT);
	}
	else if (keycode == XK_d)
	{
		new_pos.x += cub->raycaster.player.plane.x * move_speed;
		new_pos.y += cub->raycaster.player.plane.y * move_speed;
		update_dir(cub, RIGHT);
	}
	else if (keycode == XK_Escape)
		exit(mymlx_destroy(cub));

	check_collisions(cub, new_pos, old_pos);
	render_scene(cub);
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

//da levare
unsigned int	darken_color(unsigned int color, float distance)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	float factor;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	factor = 10.0f / distance;
	if (factor > 1.0f)
		factor = 1.0f;

	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);

	return ((r << 16) | (g << 8) | b);
}


