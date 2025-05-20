/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:20 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/20 09:41:17 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
# define LEFT 0
# define RIGHT 1
int render_loop(t_cub *cub)
{
	static double	last_frame_time = 0.0;
	double		current_time;
	double		delta_time;

	current_time = get_time();
	delta_time = current_time - last_frame_time;

	if (delta_time < FRAME_TIME)
	{
		usleep((FRAME_TIME - delta_time) * 1000000);
		return (0);
	}
	last_frame_time = current_time;
	key_handler(cub);
	return (render_scene(cub));
}


int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		ft_printf("Error: Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	mymlx_init(&cub, argv);

	//Matrix debug
	// int	i = 0;
	// ft_printf("Matrice della mappa (%d x %d):\n", cub.map.sizes.map_lenght, cub.map.sizes.map_height);
	// while (i < cub.map.sizes.map_height * cub.map.sizes.map_lenght)
	// {
	// 	ft_printf("%d ", cub.map.matrix[i++]);
	// 	if (i % cub.map.sizes.map_lenght == 0)
	// 		ft_printf("\n");
	// }
	// ft_printf("\n");

	mlx_hook(cub.pic.win.p, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.pic.win.p, 3, 1L << 1, key_release, &cub);
	mlx_hook(cub.pic.win.p, 17, 0, mymlx_exit, &cub);
	mlx_loop_hook(cub.p, render_loop, &cub);

	render_scene(&cub);
	mlx_loop(cub.p);

	return (0);
}

