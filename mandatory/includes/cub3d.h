/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:29:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/19 10:49:21 by apintaur         ###   ########.fr       */
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

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define CELL_SIZE 64
# define FOV 60.0f
# define VIEW_DISTANCE 15.0f
# define RENDER_SCALE 2 // con 1 è full quality, con 2 1/2 quality per grandi distanze
# define LOD_THRESHOLD 8.0f //distanza da cui switchare la qualità bassa
# define TARGET_FPS 120.0f
# define FRAME_TIME (1.0f / TARGET_FPS)

# define ROTATION_SPEED 0.05f
# define MOVE_SPEED 0.1f

# include "../libft/includes/libft.h"
# include "../.minilibx/minilibx-linux/mlx.h"
# include "../.minilibx/minilibx-linux/mlx_int.h"

# include <math.h>
# include <X11/X.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

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

typedef struct s_wall
{
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
}	t_wall;

typedef struct s_textures
{
	t_wall	wall;
}	t_textures;


typedef struct s_cub
{
	void		*p;
	t_picture	pic;
	t_map		map;
	t_raycaster	raycaster;
	t_textures	textures;
	int			frame_count;
	double		last_time;
	double		fps;
	double		fps_accum;
}	t_cub;


void	raycaster_init(t_cub *cub);

void	mymlx_pixel_put(t_image *img, int x, int y, int color);
int		render_scene(t_cub *cub);
void	cast_ray(t_ray *ray, t_player *p, t_map *map, int x);
void	map_plot(t_cub *cub);
int		mymlx_render(t_cub *cub);
int		mymlx_exit(t_cub *cub);
void	mymlx_init(t_cub *cub, char *argv[]);
int		mymlx_destroy(t_cub *cub);
int		key_hook(int keycode, t_cub *cub);
int		main_loop(t_cub *cub);
void    draw_vertical_line(t_image *img, int x, int y_start, int y_end, unsigned int color);
void    draw_horizontal_line(t_image *img, int y, int x_start, int x_end, unsigned int color);
void    fill_rectangle(t_image *img, int x, int y, int width, int height, unsigned int color);

// Funzioni per FPS counter
double	get_time();
void	init_fps_counter(t_cub *cub);
void	update_fps_counter(t_cub *cub);

//Matrix-realted functions
void	matrix_creation(t_map *map, int fd, int gnl_calls);

//Parsing functions
int	map_parsing(char *file, t_map *map);
int	get_graphics(char *file, t_map *map);
int	get_map(char *file, int gnl_calls, t_map *map);
int	is_player(char c);
int	save_image(int *i, char **dest, char *line);
int	save_color(int *i, int *dest, char *line);
int	surround_check(char *line, char *prev, char *next, int i);


//Utils
void	free_function(char *line);
int	color_helper(char *line, int j);
int	graphics_helper(char *line, int *gnl_calls, int *result, t_map *map);
void	matrix_helper(char *line, int *matrix, int *j, t_map *map);
int	check_helper(char *line, char *prev, char *next, int *player);
void	sizes_helper(char *line, int fd, t_map *map);
char	*gnl_helper(char *line, int gnl_calls, int fd);

#endif
