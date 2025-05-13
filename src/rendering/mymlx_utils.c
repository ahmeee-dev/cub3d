/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:34:20 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/12 22:48:33 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>


void	mymlx_init_spawn(t_mlx *data)
{
	/* TODO:
	**	init the spawn point of the player and adjust the FOV
	*/
	raycaster_init(&data->raycaster);
}
void	mymlx_init(t_mlx *data, char *filename)
{
	(void)filename; /* Sopprime il warning del parametro inutilizzato */

	data->mlx_p = NULL;
	data->pic.img.p = NULL;
	data->pic.win.p = NULL;
	data->mlx_p = mlx_init();
	data->pic.win.p = mlx_new_window(data->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->pic.img.p = mlx_new_image(data->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->pic.img.addr = mlx_get_data_addr(data->pic.img.p, &data->pic.img.bits_pp, \
						&data->pic.img.lenght, &data->pic.img.endian);
						/*	TODO:
						**	init parsing variables (matrix, colors, etc)
						*/

					mymlx_init_spawn(data);
					mlx_do_key_autorepeaton(data->mlx_p);
}

int	mymlx_destroy(t_mlx *data)
{
	if (data)
	{
		mlx_destroy_image(data->mlx_p, data->pic.img.p);
		mlx_destroy_window(data->mlx_p, data->pic.win.p);
		free (data->mlx_p);
		free (data->raycaster.player);
		/*	TODO:
		**	free other variables from parsing or rendering
		*/

		return (1);
	}
	return (-1);
}
