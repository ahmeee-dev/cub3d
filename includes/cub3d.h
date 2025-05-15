/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/15 07:49:46 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define WALL 1
#define FLOOR 0
#define BLANK 2

//WALL == 1
//FLOOR == 0
//BLANK == 2

# define SCREEN_WIDTH 2500
# define SCREEN_HEIGHT 1900
# define CELL_SIZE 64
# define FOV 60.0f

# include "../libft/includes/libft.h"
# include "../.minilibx/minilibx-linux/mlx.h"
# include "../.minilibx/minilibx-linux/mlx_int.h"

# include <math.h>
# include <X11/X.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

//Mlx structures
typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_image
{
	void			*p;
	void			*addr;
	int				bits_pp;
	int				lenght;
	int				endian;
	unsigned int	color;
	t_size			size;
}	t_image;

typedef struct	s_window
{
	void			*p;
	unsigned int	color;
	t_size			size;
}	t_window;

typedef struct s_picture
{
	t_image		img;
	t_window	win;
}	t_picture;

////Parsing structures
typedef struct s_sizes
{
	int		map_height;
	int		map_lenght;
}		t_sizes;

typedef struct s_data
{
	int		floor;
	int		ceiling;
	char	*nt;
	char	*st;
	char	*et;
	char	*wt;
}		t_data;

typedef struct	s_map
{
	t_data		data;
	t_sizes		sizes;
	int			*matrix;
}		t_map;

//Rendering structures

typedef struct s_2fpoint
{
	float	x;
	float	y;
}	t_2fpoint;

typedef struct s_2ipoint
{
	int		x;
	int		y;
}	t_2ipoint;

typedef struct s_player
{
	t_2fpoint	pos;
	t_2fpoint	dir;
	t_2fpoint	plane;
}	t_player;

typedef struct s_ray
{
	t_2fpoint	dir;
	t_2fpoint	side_dist; //Distanza del player dalla fine della cella
	t_2fpoint	delta_dist;	//Distanza tra due intersezioni consecutive sullo stesso asse
	t_2ipoint	cell_pos; //Coordinate della cella in cui si trova il raggio (dove si fa DDA)
	t_2ipoint	step; //Contatore per switchare cella (passo)
	float		perp_wall_dist;	//Distanza tra il player e il muro
	int			side; //Indicatore della parte del muro colpita (verticale / orizzontale)
	int			line_height; //Altezza del muro
	int			draw_start; //Pixel di inizio del disegno della colonna x
	int			draw_end; //Pixel di fine del disegno della colonna x
}	t_ray;

typedef struct s_raycaster
{
	t_player	player;
	t_ray		*rays;
}	t_raycaster;

typedef struct s_cub
{
	void		*p;
	t_picture	pic;
	t_map		map;
	t_raycaster	raycaster;
}	t_cub;

void	raycaster_init(t_cub *cub);

void	mymlx_pixel_put(t_image *img, int x, int y, int color);
unsigned int darken_color(unsigned int color, float distance);
int		render_scene(t_cub *cub);
void	cast_ray(t_ray *ray, t_player *p, t_map *map, int x);
void	map_plot(t_cub *cub);
int		mymlx_render(t_cub *cub);
int		mymlx_exit(t_cub *cub);
void	mymlx_init(t_cub *cub, int argc, char *argv[]);
int		mymlx_destroy(t_cub *cub);
int		key_hook(int keycode, t_cub *cub);
int		main_loop(t_cub *cub);

//Matrix-realted functions
void	matrix_creation(t_map *map, int fd, int gnl_calls);

//Parsing functions
int	map_parsing(char *file, t_map *map);
int	get_graphics(char *file, t_map *map);
int	get_map(char *file, int gnl_calls, t_map *map);

//Utils
void	free_function(char *line);

#endif
