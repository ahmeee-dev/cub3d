/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:30:00 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/16 07:49:02 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <sys/time.h>

static void snprintf_fps(char *buffer, int size, int value)
{
	char *digits = "0123456789";
	char tmp[12];
	int i = 0;
	int reverse_i = 0;

	if (value == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return;
	}

	while (value > 0 && i < 10)
	{
		tmp[i++] = digits[value % 10];
		value /= 10;
	}

	while (i > 0 && reverse_i < size - 1)
	{
		buffer[reverse_i++] = tmp[--i];
	}

	buffer[reverse_i] = '\0';
}

double	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	init_fps_counter(t_cub *cub)
{
	cub->frame_count = 0;
	cub->last_time = get_time();
	cub->fps = 0.0;
	cub->fps_accum = 0.0;
}

void	update_fps_counter(t_cub *cub)
{
	double	current_time;
	double	frame_time;
	static char	fps_text[32] = "FPS: 0";
	int	rounded;

	current_time = get_time();
	frame_time = current_time - cub->last_time;
	cub->last_time = current_time;
	cub->fps_accum += frame_time;
	cub->frame_count += 1;
	if (cub->fps_accum >= 1.0)
	{
		cub->fps = cub->frame_count / cub->fps_accum;
		rounded = (int)(cub->fps + 0.5);
		fps_text[0] = 'F';
		fps_text[1] = 'P';
		fps_text[2] = 'S';
		fps_text[3] = ':';
		fps_text[4] = ' ';
		snprintf_fps(&fps_text[5], sizeof(fps_text) - 5, rounded);
		cub->fps_accum = 0.0;
		cub->frame_count = 0;
	}
	mlx_string_put(cub->p, cub->pic.win.p,
		10, 20, 0xFFFFFF, fps_text);
}
