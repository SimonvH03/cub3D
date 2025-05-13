/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandatory_cub3d.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/12 18:47:31 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/05/13 13:25:51 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_CUB3D_H
# define MANDATORY_CUB3D_H
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
// libraries
# include "MLX42/MLX42.h"
# include "libft.h"

// mlx window configuration
# define WINDOW_TITLE		"cub3d"
# define WINDOW_WIDTH		1280
# define WINDOW_HEIGHT		720
# define FULLSCREEN			false
# define MONITOR_ID			0

// ratio of wall height / width
# define CAMERA_PLANE		1

# define VALID_MAP_CHAR	"01NESW "

# define FLOOD_SHIFT		7
# define FLOOD_MASK			0x80
# define TYPE_MASK			0x007F

// player defaults
# define MOVEMENT_SPEED		4
# define ROTATION_SPEED		2
# define COLLISION_HITBOX	0.2

typedef struct s_camera
{
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plane_y;
	float			plane_x;
	float			rotation_cosin[2];
	float			movement_matrix[3][3];
	float			movement_speed;
	float			aspect_ratio;
}	t_camera;

typedef struct s_walls
{
	mlx_image_t			*image;
	mlx_texture_t		*north;
	mlx_texture_t		*east;
	mlx_texture_t		*south;
	mlx_texture_t		*west;
}	t_walls;

typedef struct s_grid
{
	char			**tilemap;
	unsigned int	y_max;
	unsigned int	x_max;
}	t_grid;

typedef struct s_scene
{
	t_walls			walls;
	t_grid			grid;
	uint32_t		floor_clr;
	uint32_t		ceiling_clr;
}	t_scene;

typedef struct s_window
{
	mlx_t			*mlx;
	t_camera		camera;
	t_scene			scene;
	mlx_image_t		*fps;
	t_list			*texture_allocations;
}	t_window;

enum	e_hit_axis
{
	ha_horizontal,
	ha_vertical
};

typedef struct s_column
{
	int32_t			half_height;
	int32_t			start;
	int32_t			end;
	mlx_texture_t	*texture;
	float			x;
	float			step;
	float			tex_y;
}	t_column;

typedef struct s_ray
{
	uint32_t		pos_x;
	uint32_t		pos_y;
	float			camera_x;
	float			dir_x;
	float			dir_y;
	float			step_x;
	float			step_y;
	float			total_x;
	float			total_y;
	float			start_x;
	float			start_y;
	float			partial;
	float			distance;
	short			sign_x;
	short			sign_y;
	bool			hit_type;
}	t_ray;

// global internal errno
extern int	g_cub_errno;
typedef enum e_cub_errno
{
	CUB_SUCCESS = 0,	// No Errors.
	CUB_MLXFAIL,		// MLX42 function has failed.
	CUB_LIBFTFAIL,		// Libft function has failed.
	CUB_MEMFAIL,		// Dynamic memory allocation has failed.
	CUB_INVFILE,		// The provided file was invalid or does not exist.
	CUB_ELEMFORM,		// Scene element has invalid type identifier.
	CUB_CLRFORM,		// Scene colour has invalid format.
	CUB_NOCLR,			// Scene colour is missing.
	CUB_TEXPATH,		// Scene texture path was invalid or does not exist.
	CUB_TEXFORM,		// Scene texture has invalid format.
	CUB_NOTEX,			// Scene texture is missing.
	CUB_NOMAP,			// Scene map is missing.
	CUB_MAPCHAR,		// Scene map has invalid character.
	CUB_MAPPERIM,		// Scene map not closed/surrounded by walls.
	CUB_NOPLAY,			// Scene map has no player position.
	CUB_MULTPLAY,		// Scene map has multiple player positions.
	CUB_ERRMAX,			// Error count
}	t_cub_errno;

typedef	int		(griditer_func)(
					t_grid *grid,
					unsigned int y,
					unsigned int x,
					void *param);
int			
	gridmap_iter(
		t_grid *grid,
		griditer_func function,
		void *param);
// error
int			
	set_error(
		const int err_val);
void		
	print_error(void);
// allocations
int			
	add_to_texture_list(
		t_window *window,
		mlx_texture_t *texture_ptr);
void		
	empty_texture_list(
		t_window *window);

// // INIT
// window
int			
	init_window(
		t_window *window);

// scene (parsing)
int			
	init_game(
		t_window *window,
		t_scene *scene,
		const char *input_file);
int			
	read_elements(
		t_window *window,
		t_scene *scene,
		char ***content);
int			
	read_tilemap(
		t_grid *grid,
		char *const *content);
int			
	perimeter_check(
		t_grid *grid,
		unsigned int y,
		unsigned int x,
		void *param);
// player (parsing)
int			
	init_player(
		t_camera *camera,
		t_grid *grid);

// // LOOP
// mlx loop hooks
void		
	view_manager(
		void *param);
void		
	window_keyhook(
		mlx_key_data_t key_data,
		void *param);
// player control
void		
	wasd_move(
		mlx_t *mlx,
		t_grid *grid,
		t_camera *camera);
void		
	arrowkey_look(
		mlx_t *mlx,
		t_camera *camera);

// render
void		
	draw_texture_column(
		t_ray *ray,
		t_walls *walls,
		uint32_t x);
void		
	raycast(
		t_scene *scene,
		t_camera *camera);

// // ModLX, for when MLX42 just doesn't cut it
mlx_texture_t
	*modlx_load_xpm42(
		const char *path);
int			
	modlx_put_string(
		mlx_image_t *strimage,
		const char *str);
mlx_image_t	
	*modlx_imgcpy(
		mlx_image_t *dest,
		mlx_image_t *src);
int			
	transpose_texture(
		mlx_texture_t *texture);

// arithmetic and maths
typedef union u_inv_sqrt
{
	float	as_float;
	int32_t	as_int;
}	t_q3;

void		
	normalize_vector2(
		float *x_component,
		float *y_component);
float		
	ft_abs_float(
		float value);
short		
	ft_sign_float(
		float value);
int			
	ft_clamp(
		int a,
		int lower_bound,
		int upper_bound);
int			
	ft_min_int(
		int a,
		int b);
char		
	set_tilemap_cell(
		const char type);
char		
	get_type(const char cell);

#endif
