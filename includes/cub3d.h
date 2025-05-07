/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/07 11:08:06 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WIDTH 1920
#define HEIGHT 1080

#include "../libft/includes/libft.h"
#include "../.minilibx/minilibx_opengl_20191021/mlx.h"
#include "../.minilibx/minilibx_opengl_20191021/mlx_int.h"
#include <unistd.h>

typedef struct	s_colors
{
	int	floor;
	int	ceiling;
	char	*nt;
	char	*st;
	char	*et;
	char	*wt;
}		t_colors;

typedef struct s_color
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}	t_point;

typedef struct s_window
{
	void			*p;
	unsigned int	color;
}	t_window;

typedef struct s_image
{
	void			*p;
	char			*addr;
	int				bits_pp;
	int				lenght;
	int				endian;
	unsigned int	color;
}	t_image;

typedef struct	s_picture
{
	t_window	win;
	t_image		img;
}	t_picture;

typedef struct s_mlx
{
	void		*mlx_p;
	t_picture	pic;
}	t_mlx;



//Rendering functions
int		mymlx_exit(t_mlx *data);
int		mymlx_render(t_mlx *data);
int		mymlx_destroy(t_mlx *data);
void	mymlx_init_spawn(t_mlx *data);
void	mymlx_init(t_mlx *data, char *filename);
void	mymlx_pixel_put(t_mlx *data, int x, int y, int color);

#endif
