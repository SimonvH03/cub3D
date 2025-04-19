/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/04/19 01:00:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "MLX42/MLX42_Int.h"
# include "libft.h"
# include "gamestate.h"
# include "hud.h"
# include "paths.h"
# include "render.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

// mlx window
# define WINDOW_TITLE		"cub3d"
# define FULLSCREEN			false
# define MONITOR_ID			1
# define WIDTH				1280
# define HEIGHT				720

// UI colours 0xAaBbGgRr
# define C_TRANSPARENT		0x00000000
# define C_TRANSLUCENT		0x42000000
# define C_CEILING			0xBB000000
# define C_FLOOR			0x80424242
# define C_WALL				0xFF2A66C0
# define C_DOOR				0xFF153360
# define C_OPENDOOR			0xFF00C0C0
# define C_ERROR			0xFF80FF00

// ratio of wall height / width
# define CAMERA_PLANE		1

# define MINIMAP_SCALE		10
# define DOOR_SHIFT_SPEED	1
# define INTERACTION_RANGE	1.5

# define MLX_FONT_WIDTH		10

// player defaults
# define MOVEMENT_SPEED		4
# define ROTATION_SPEED		2
# define CURSOR_ROT_SPEED	50
# define COLLISION_HITBOX	0.2

// stuff that should be in the .cub file
# define G1_MAG_CAPACITY	9
# define G1_SPARE_MAGS		4
# define G1_FRAME_RATE		16

typedef struct s_window
{
	mlx_t					*mlx;
	mlx_cursor_t			*cursor;
	t_scene					scene;
	t_menu					menu;
	t_hud					hud;
	t_list					*texture_allocations;
	enum e_window_view		view;
}	t_window;

// compile with bonus
# define VALID_MAP_CHAR		"01NESW dD"

// # define VALID_MAP_CHAR		"01NESW "

extern int				g_cub_errno;

typedef enum cub_errno
{
	CUB_SUCCESS = 0,	// No Errors.
	CUB_MLXFAIL,		// MLX42 function has failed.
	CUB_LIBFTFAIL,		// Libft function has failed.
	CUB_MEMFAIL,		// Dynamic memory allocation has failed.
	CUB_INVFILE,		// The provided file was invalid / does not exist.
	CUB_INVELEM,		// Cub element has invalid type identifier.
	CUB_INVCLR,			// Cub colour has invalid format. (R,G,B [0,255])
	CUB_NOCLR,			// Cub colour is missing.
	CUB_INVTEX,			// Cub texture has invalid format. (png, xpm42)
	CUB_NOTEX,			// Cub texture is missing.
	CUB_NOMAP,			// Cub map is missing.
	CUB_INVMAP,			// Cub map has invalid character. (0,1,N,S,E,W,' ')
	CUB_PERIM,			// Cub map not closed/surrounded by walls.
	CUB_NOPLAY,			// Cub map has no player position.
	CUB_MULTPLAY,		// Cub map has multiple player positions.
	CUB_INVDOOR,		// Cub map has invalid door placement.
	CUB_ERRMAX			// Error count
}	cub_errno_t;

typedef union u_inv_sqrt
{
	float	as_float;
	int32_t	as_int;
}	t_q3;

typedef	void
	(imgiter_func)(
		mlx_image_t *image,
		uint32_t x,
		uint32_t y,
		void *param);
typedef	int
	(griditer_func)(
		t_grid *grid,
		unsigned int y,
		unsigned int x,
		void *param);

void
	image_iter(
		mlx_image_t *image,
		imgiter_func function,
		void *param);
int
	gridmap_iter(
		t_grid *grid,
		griditer_func function,
		void *param);

int
	set_error(
		const int err_val);

void
	print_error(void);

int
	add_to_texture_list(
		t_window *window,
		mlx_texture_t *texture_ptr);
void
	empty_texture_list(
		t_window *window);

int
	new_scaled_image(
		mlx_t *mlx,
		t_scalable *dest);
void
	sample_scalable(
		mlx_image_t *dest,
		uint32_t img_x,
		uint32_t img_y,
		void *param);

//// PHASE 0: initialising mlx window, game, hud and menu
int
	init_window(
		t_window *window);

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
int
	init_doors(
		t_grid *grid);
int
	init_player(
		t_player *player,
		t_grid *grid);
int
	init_weapon(
		t_window *window,
		t_weapon *weapon);

int
	init_hud(
		t_window *window,
		t_hud *hud,
		t_scene *scene);
int
	new_images_minimap(
		mlx_t *mlx,
		t_minimap *minimap);
int
	new_images_bigmap(
		mlx_t *mlx,
		t_bigmap *map,
		t_scene *scene);

int
	init_menu(
		t_window *window,
		t_menu *menu);

int
	set_view_depths(
		t_window *window);

// MLX_HOOKS
void
	frametime_dependant_variables(
		void *param);
void
	view_manager(
		void *param);
void
	window_keyhook(
		mlx_key_data_t key_data,
		void *param);
void
	mouse_buttons(
		mouse_key_t button,
		action_t action,
		modifier_key_t mods,
		void *param);

// user inputs
void
	wasd_move(
		mlx_t *mlx,
		t_grid *grid,
		t_camera *camera);
void
	arrowkey_look(
		mlx_t *mlx,
		t_camera *camera);
void
	mouse_pan(
		mlx_t *mlx,
		t_camera *camera);
void
	fire_weapon(
		t_weapon *weapon);
void
	reload_weapon(
		t_weapon *weapon);
void
	update_weapon_animation(
		mlx_t *mlx,
		t_weapon *weapon);
void
	player_interaction(
		t_grid *grid,
		t_camera *camera);
void
	operate_door(
		t_door *door,
		t_camera *camera);
void
	update_doors(
		t_grid *grid,
		float delta_time);
void
	hover_button(
		t_menu *menu,
		t_window *window);
void
	click_button(
		t_menu *menu,
		t_window *window);
void
	select_button(
		t_menu *menu,
		keys_t key);
void
	confirm_selection(
		t_menu *menu,
		t_window *window);
void
	toggle_maps(
		t_hud *hud);
void
	toggle_view(
		t_window *window);

// render
void
	raycast(
		t_scene *scene);
void
	cast_ray(
		t_ray *ray,
		t_grid *grid);
void
	draw_texture_column(
		t_ray *ray,
		t_walls *walls,
		t_camera *camera,
		uint32_t x);

// hud
void
	update_minimap(
		t_minimap *minimap);
void
	update_bigmap(
		t_bigmap *map);

// modlx
mlx_texture_t	*
	modlx_load_xpm42(
		const char *path);
int
	modlx_put_string(
		mlx_image_t *strimage,
		const char *str);
mlx_image_t	*
	modlx_imgcpy(
		mlx_image_t *dest,
		mlx_image_t *src);
int
	transpose_texture(
		mlx_texture_t *texture);

// setters getters of (mlx_image_t *)->enabled bit
void
	set_minimap_ability(
		t_minimap *minimap,
		bool ability);
bool
	get_minimap_ability(
		t_minimap *minimap);
void
	set_bigmap_ability(
		t_bigmap *bigmap,
		bool ability);
bool
	get_bigmap_ability(
		t_bigmap *bigmap);
void
	set_menu_ability(
		t_menu *menu,
		bool ability);
void
	set_scene_ability(
		t_scene *scene,
		bool ability);

// arithmetic and maths
float
	nearest_power_of_2(
		float value);
float
	ft_max_float(
		float a,
		float b);
float
	ft_min_float(
		float a,
		float b);
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
	ft_max_int(
		int a,
		int b);
int
	ft_min_int(
		int a,
		int b);
int
	ft_abs_int(
		int value);
short
	ft_sign_int(
		int value);

void
	normalize_vector2(
		float *x_component,
		float *y_component);

// tilemap_cell
int16_t
	set_cell(
		const bool solid,
		const int id,
		const char type);
bool
	is_solid(
		const int16_t cell);
bool
	get_axis(
		const int16_t cell);
int
	get_id(
		const int16_t cell);
char
	get_type(
		const int16_t cell);
bool
	is_door(
		const int16_t cell);

#endif