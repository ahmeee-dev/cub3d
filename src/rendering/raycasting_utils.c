/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:20:32 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 09:54:14 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#include <stdlib.h>

void	player_init(t_raycaster *rc)
{
	rc->player = (t_player *) malloc(sizeof(t_player));
	if (!rc->player)
	{
		ft_printf("Error: malloc failed in %s\n", __func__);
		exit (EXIT_FAILURE);
	}

	// Posizione iniziale del giocatore (stanza centrale)
	rc->player->pos.x = SCREEN_WIDTH / 2.0f;
	rc->player->pos.y = SCREEN_HEIGHT / 2.0f;

	// Direzione iniziale (verso est)
	rc->player->dir.x = 1.0f;
	rc->player->dir.y = 0.0f;

	// Piano di proiezione per FOV
	rc->player->plane.x = 0.0f;
	rc->player->plane.y = tanf((FOV * M_PI / 180.0f) / 2.0f);

	rc->player->angle = 0.0f; // Sta guardando a est
}

void	rays_init(t_raycaster *rc)
{
	rc->rays = (t_ray *) malloc(sizeof(t_ray) * SCREEN_WIDTH);
	if (!rc->rays)
	{
		ft_printf("Error: malloc failed in %s\n", __func__);
		free (rc->player);
		exit (EXIT_FAILURE);
	}
	ft_memset(rc->rays, 0, sizeof(t_ray) * SCREEN_WIDTH);
}

void	raycaster_init(t_raycaster *rc)
{
	player_init(rc);
	rays_init(rc);
	rc->proj_plane_dist = (SCREEN_WIDTH / 2.0f) / tanf((FOV * M_PI / 180.0f) / 2.0f);
}
