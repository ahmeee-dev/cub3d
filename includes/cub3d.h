/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 11:04:13 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WALL 49
#define FLOOR 48

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define CELL_SIZE 64
# define FOV 60.0f

# include "vectors.h"
# include "../libft/includes/libft.h"
# include "../.minilibx/minilibx_opengl_20191021/mlx.h"
# include <unistd.h>
# include <OpenGL/gl3.h>
# include <stdlib.h>
# include <math.h>

//Mlx data


typedef struct	s_sizes
{
	int		map_height;
	int		map_lenght;
}		t_sizes;

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

typedef struct s_picture
{
	t_window	win;
	t_image		img;
}	t_picture;

//Cub3d data
typedef struct s_colors
{
	int		floor;
	int		ceiling;
	char	*nt;
	char	*st;
	char	*et;
	char	*wt;
}		t_colors;

typedef struct s_player
{
	t_2fpoint	pos;
	t_2fpoint	dir;
	t_2fpoint	plane;
	float		angle;
}	t_player;

typedef struct s_ray
{
	t_2fpoint	dir;
	t_2fpoint	side_dist;
	t_2fpoint	delta_dist;
	t_2fpoint	step;
	t_2ipoint	map;
	float		perp_wall_dist;
	int			hit_wall;
	int			hit_axe;
}	t_ray;

typedef struct s_raycaster
{
	t_player	*player;
	t_ray		*rays;
	float		proj_plane_dist;
}	t_raycaster;

typedef struct	s_data
{
	t_colors	colors;
	t_sizes		sizes;
	int		*matrix;
}		t_data;

typedef struct s_mlx
{
	t_data		data;
	void		*mlx_p;
	t_picture	pic;
	t_raycaster	raycaster;
}	t_mlx;

typedef struct s_map
{
	t_3fpoint	p;
	int			type;
}	t_map;

//Cub3d functions
void	raycaster_init(t_raycaster *rc);
t_map	*map_get(int width, int height);
void 	map_plot(t_mlx *data);

//Mlx functions
int		mymlx_exit(t_mlx *data);
int		mymlx_render(t_mlx *data);
int		mymlx_destroy(t_mlx *data);
void	mymlx_init_spawn(t_mlx *data);
void	mymlx_init(t_mlx *data, char *filename);
void	mymlx_pixel_put(t_mlx *data, int x, int y, int color);

//Matrix-realted functions
void	matrix_creation(t_mlx *data, int fd, int gnl_calls);

//Parsing functions
int	map_parsing(char *file, t_data *data);
int	get_graphics(char *file, t_data *data);
int	get_map(int fd, int gnl_calls, t_data *data);
#endif
