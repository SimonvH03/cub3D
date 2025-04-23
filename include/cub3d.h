/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/04/23 17:55:50 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
// libraries
# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"
# include "libft.h"
// chopped up headers for some reason
# include "gamestate.h"
# include "hud.h"
# include "paths.h"
# include "player.h"
# include "render.h"

// mlx window configuration
# define WINDOW_TITLE		"cub3d"
# define WINDOW_WIDTH		1280
# define WINDOW_HEIGHT		720
# define FULLSCREEN			false
# define MONITOR_ID			0

# ifdef BONUS
#  define VALID_MAP_CHAR	"01NESW dD"
# else
#  define VALID_MAP_CHAR	"01NESW "
# endif

enum	e_window_view
{
	wv_menu,
	wv_game
};

typedef struct s_window
{
	mlx_t					*mlx;
	mlx_cursor_t			*cursor;
	t_hud					hud;
	t_menu					menu;
	t_player				player;
	t_scene					scene;
	t_list					*texture_allocations;
	enum e_window_view		view;
}	t_window;

// global internal errno
extern int	g_cub_errno;
typedef enum e_cub_errno
{
	CUB_SUCCESS = 0,	// No Errors.
	CUB_MLXFAIL,		// MLX42 function has failed.
	CUB_LIBFTFAIL,		// Libft function has failed.
	CUB_MEMFAIL,		// Dynamic memory allocation has failed.
	CUB_DATAFAIL,		// Data file failed to load.
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
	CUB_ERRMAX,			// Error count
}	t_cub_errno;

typedef	void	(imgiter_func)(
					mlx_image_t *image,
					uint32_t x,
					uint32_t y,
					void *param);
typedef	int		(griditer_func)(
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
// scalable images
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

// // INIT
// window
int			
	init_window(
		t_window *window);

// scene
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

// player
int			
	init_player(
		t_player *player,
		t_grid *grid);
int			
	init_weapon(
		t_window *window,
		t_weapon *weapon);
// hud
int			
	init_hud(
		t_window *window,
		t_hud *hud);
int			
	new_images_minimap(
		mlx_t *mlx,
		t_minimap *minimap);
int			
	new_images_bigmap(
		mlx_t *mlx,
		t_bigmap *map);
// menu
int			
	init_menu(
		t_window *window,
		t_menu *menu);
// image stack sorting
int			
	set_view_depths(
		t_window *window);

// // LOOP
// mlx loop hooks
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
// player control
void		
	mouse_pan(
		mlx_t *mlx,
		t_camera *camera);
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
	player_interaction(
		t_grid *grid,
		t_camera *camera);
// menu control
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
// view control
void		
	toggle_maps(
		t_hud *hud);
void		
	toggle_view(
		t_window *window);
// gamestate
void		
	fire_weapon(
		t_weapon *weapon);
void		
	reload_weapon(
		t_weapon *weapon);
void		
	update_weapon(
		mlx_t *mlx,
		t_weapon *weapon);
void		
	operate_door(
		t_door *door,
		t_camera *camera);
void		
	update_doors(
		t_grid *grid,
		float delta_time);

// render
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
void		
	raycast(
		t_scene *scene,
		t_camera *camera);
void		
	update_bigmap(
		t_bigmap *map);
void		
	update_minimap(
		t_minimap *minimap);

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

// setters getters of mlx_image_t.enabled bits
// groups
void		
	set_bigmap_ability(
		t_bigmap *bigmap,
		bool ability);
bool		
	get_bigmap_ability(
		t_bigmap *bigmap);
void		
	set_minimap_ability(
		t_minimap *minimap,
		bool ability);
bool		
	get_minimap_ability(
		t_minimap *minimap);
// layers
void		
	set_menu_ability(
		t_menu *menu,
		bool ability);
void		
	set_scene_ability(
		t_scene *scene,
		t_weapon *weapon,
		bool ability);

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
	nearest_power_of_2(
		float value);
float		
	ft_abs_float(
		float value);
float		
	ft_max_float(
		float a,
		float b);
float		
	ft_min_float(
		float a,
		float b);
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

// tilemap cell composition
int16_t		
	set_tilemap_cell(
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
bool		
	is_wall(
		const int16_t cell);

#endif
