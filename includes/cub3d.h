/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 10:13:36 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WALL 49
#define FLOOR 48
#define BLANK -1
#define WIDTH 1920
#define HEIGHT 1080

#include "../libft/includes/libft.h"
#include "../.minilibx/minilibx_opengl_20191021/mlx.h"
#include "../.minilibx/minilibx_opengl_20191021/mlx_int.h"
#include <unistd.h>

typedef struct	s_data
{
	t_colors	colors;
	t_sizes		sizes;
	int		*matrix;
}		t_data;

typedef struct	s_sizes
{
	int		map_height;
	int		map_lenght;
}		t_sizes;

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

//Parsing functions
void	map_parsing(char *file, t_data *data);
int	map_save(char *file, int gnl_calls, t_data *data);
int	get_graphics(char *file, t_data *data);
//Matrix-realted functions
void	matrix_creation(t_data *data, int fd, int gnl_calls);

#endif
