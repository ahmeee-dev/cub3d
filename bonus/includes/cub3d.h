/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:24:17 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/21 10:05:13 by apintaur         ###   ########.fr       */
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

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define CELL_SIZE 64
# define FOV 60.0f
# define VIEW_DISTANCE 15.0f
# define RENDER_SCALE 2 // con 1 è full quality, con 2 1/2 quality per grandi distanze
# define LOD_THRESHOLD 1.0f //distanza da cui switchare la qualità bassa
# define TARGET_FPS 60.0f

# define ROT_SPD 0.1f
# define MOVE_SPEED 0.2f

# define MAX_DIST 1e30

# define MOUSE_SPEED 4
// Minimap definitions
# define MINIMAP_SCALE_FACTOR 100
# define MINIMAP_CELL_SIZE (SCREEN_WIDTH / MINIMAP_SCALE_FACTOR)
# define MINIMAP_PLAYER_SIZE (MINIMAP_CELL_SIZE / 3)
# define MINIMAP_RIGHT_MARGIN (SCREEN_WIDTH / 80)
# define MINIMAP_OFFSET_Y (SCREEN_HEIGHT / 60)

// Minimap colors
# define MINIMAP_WALL_COLOR 0x333333
# define MINIMAP_FLOOR_COLOR 0xFFFFFFFF
# define MINIMAP_PLAYER_COLOR 0xFF0000
# define FOV_FILL_COLOR 0xFFFF00

// FOV drawing parameters
# define FOV_ANGLE_STEP 0.06f
# define FOV_RADIANS 1.151917f

# include "../../libft/includes/libft.h"
# include "../../.minilibx/minilibx-linux/mlx.h"
# include "../../.minilibx/minilibx-linux/mlx_int.h"

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
	char	*wall;
	char	*door;
	char	*gun1;
	char	*gun2;
	char	*ceiling1;
	char	*ceiling2;
	char	*ceiling3;
	char	*hand;
	char	*floor1;
	char	*floor2;
	char	*floor3;
	char	*floor4;
	char	*floor5;
	char	*floor6;
	char	*floor7;
	char	*floor8;
}		t_data;

typedef struct s_cell_tex
{
	int	floor_tex_idx;
	int	ceiling_tex_idx;
}	t_cell_tex;

typedef struct	s_map
{
	t_data			data;
	t_sizes		sizes;
	int			*matrix;
	char			**map;
	int				width;
	int				height;
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
	t_image	wall;
	t_image	door;
	t_image	gun_nofire;
	t_image	gun_fire;
	t_image	ceiling_light;
	t_image	ceiling_nolight[2];
	t_image	hand;
	t_image floor_light[4];
	t_image floor_nolight[4];
}	t_textures;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_cub
{
	void		*p;
	t_picture	pic;
	t_map		map;
	t_raycaster	raycaster;
	t_textures	textures;
	t_keys		keys;
	int			frame_count;
	double		last_time;
	double		fps;
	double		fps_accum;
	int			mouse_x;
	int			mouse_times;
}	t_cub;



void	mymlx_pixel_put(t_image *img, int x, int y, int color);
int		mymlx_render(t_cub *cub);
void	mymlx_init(t_cub *cub, char *argv[]);
int		mymlx_exit(t_cub *cub);
int		mymlx_destroy(t_cub *cub);
void	raycaster_init(t_cub *cub);
void	draw_minimap(t_cub *cub);
void	draw_vertical_line(t_image *img, int x, t_2ipoint range, unsigned int color);
int		render_scene(t_cub *cub);
void	cast_ray(t_ray *ray, t_player *p, t_map *map, int x);
void	key_handler(t_cub *cub);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);

void	run_dda_algorithm(t_ray *ray, t_map *map);
void	draw_texture_line(t_cub *cub, t_ray *ray, t_image *w_texture, int x);
void	render_column(t_cub *cub, int x, unsigned int ceiling_color,
		unsigned int floor_color);
void	fill_remaining_columns(t_cub *cub, t_ray *ray, int x,
		unsigned int ceiling_color, unsigned int floor_color);
t_image	*get_floor_type(t_cub *cub, int cell_x, int cell_y);
t_image	*get_ceiling_type(t_cub *cub, int cell_x, int cell_y);
void	draw_floor(t_cub *cub, t_ray *ray, int x);
int		mouse_move(int x, int y, void *param);
void	update_dir(t_cub *cub, int type);

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
void	check_collisions(t_cub *cub, t_2fpoint new_pos, t_2fpoint old_pos);
void	free_function(char *line);
int		color_helper(char *line, int j);
int		graphics_helper(char *line, int *gnl_calls, int *result, t_map *map);
void	matrix_helper(char *line, int *matrix, int *j, t_map *map);
int		check_helper(char *line, char *prev, char *next, int *player);
void	sizes_helper(char *line, int fd, t_map *map);
char	*gnl_helper(char *line, int gnl_calls, int fd);

#endif
