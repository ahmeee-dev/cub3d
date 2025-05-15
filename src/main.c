/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:38:20 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 08:38:21 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_loop(t_cub *cub)
{
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

	mymlx_init(&cub, argc, argv);

	int	i = 0;
	ft_printf("Matrice della mappa (%d x %d):\n", cub.map.sizes.map_lenght, cub.map.sizes.map_height);
	while (i < cub.map.sizes.map_height * cub.map.sizes.map_lenght)
	{
		ft_printf("%d ", cub.map.matrix[i++]);
		if (i % cub.map.sizes.map_lenght == 0)
			ft_printf("\n");
	}
	ft_printf("\n");

	mlx_hook(cub.pic.win.p, 2, 1L << 0, key_hook, &cub);
	mlx_hook(cub.pic.win.p, 17, 0, mymlx_exit, &cub);
	mlx_loop_hook(cub.p, render_loop, &cub);

	render_scene(&cub);
	mlx_loop(cub.p);

	return (0);
}

