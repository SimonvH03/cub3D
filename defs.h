/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2025/01/26 13:29:05 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H
# include "MLX42/include/MLX42/MLX42_Int.h"
# include "libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

// mlx window
# define WINDOW_TITLE "cub3d"
# define WIDTH				1920
# define HEIGHT				1200

# define MAX_AMMO           9

// colours
# define C_TRANSPARENT		0x00
# define C_TRANSLUCENT		0x42
# define C_CEILING			0x000000BB
# define C_FLOOR			0x42424280
# define C_WALL				0xBF6629FF
# define C_ERROR			0x00FF80FF

// camera defaults
# define MOVEMENT_SPEED		6
# define ROTATION_SPEED		3
# define COLLISION_HITBOX	0.3
// ratio of cube height / width
# define CAMERA_PLANE		1

// current window view
enum	e_view
{
	MENU,
	GAME,
	MAP
};

// raycasting DDA wall hit
enum	e_hit_axis
{
	HORIZONTAL,
	VERTICAL
};

// Map tile types and states
enum e_tile_type
{
	TILE_EMPTY = 0,
	TILE_WALL = 1,
	TILE_DOOR = 2,
	TILE_DOOR_OPEN = 3
};

// Door state structure
typedef struct s_door
{
	bool			is_opening;
	bool			is_closing;
	float			animation_progress;
	float			animation_speed;
	int				x;
	int				y;
}	t_door_state;

typedef struct s_hit
{
	int				pos_x;
	int				pos_y;
	float			distance;
	bool			is_door;
	bool			hit_type;
	t_door_state			*door_state;
}	t_hit;

typedef struct s_ray
{
	float			camera_x;
	int				pos_x;
	int				pos_y;
	float			dir_x;
	float			dir_y;
	float			step_x;
	float			step_y;
	float			total_x;
	float			total_y;
	short			sign_x;
	short			sign_y;
	bool			hit_type;
	float			distance;
	t_hit			door_hit;
	t_hit			wall_hit;
	bool			has_door;
	bool			has_wall;
}	t_ray;

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

typedef struct s_health_bar
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	float			current_health;
	float			max_health;
	uint32_t		x_pos;
	uint32_t		y_pos;
	uint32_t		width;
	uint32_t		height;
}	t_health_bar;

typedef struct s_column
{
	int				height;
	int				start;
	int				end;
	mlx_texture_t	*texture;
	float			x;
	float			step;
	float			y;
}	t_column;

typedef struct s_camera
{
	float			aspect_ratio;
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plane_y;
	float			plane_x;
	short			sign_rotate;
	float			rotation_cosin[2];
	float			movement_matrix[3][3];
	float			movement_speed;
}	t_camera;

typedef struct s_weapon
{
    mlx_image_t     *image;
    mlx_texture_t   *texture;
    mlx_texture_t   *textures[34];  // Array to store all weapon textures (6 shoot + 28 reload)
    uint32_t        x_pos;
    uint32_t        y_pos;
    float           scale;
    bool            enabled;
    int             current_frame;  // Current frame
    bool            is_animating;   // Whether animation is in progress
    bool            is_reloading;   // Whether weapon is reloading
    float           frame_time;     // Time accumulator for frame updates
    float           frame_delay;    // Delay between frames
    int             ammo_count;     // Current ammo count
}   t_weapon;

typedef struct s_ammo_display
{
    mlx_image_t     *image;
    mlx_texture_t   *number_textures[10];  // 0-9 digits
    mlx_texture_t   *slash_texture;        // / symbol
    uint32_t        x_pos;
    uint32_t        y_pos;
}   t_ammo_display;

typedef struct s_scene
{
	mlx_image_t		*walls;
	mlx_image_t		*background;
	t_camera		camera;
	char			*name;
	char			**content;
	char			**r_content;
	int				**map;
	int				y_max;
	int				x_max;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*door_texture;
	mlx_texture_t	*door_texture2;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*crosshair_texture;
	mlx_image_t		*crosshair;
	uint32_t		floor;
	uint32_t		ceiling;
	bool			recast;	
	int				max_doors;        
	t_door_state	*doors;
	int				door_count;
	t_health_bar	health_bar;     	
	t_weapon        weapon;
    t_ammo_display  ammo_display;      
}	t_scene;

typedef struct s_minimap
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	uint8_t			*circle_overlay;
	t_scene			*r_scene;
	uint32_t		side;
	uint32_t		radius;
	float			block_size;
	bool			enabled;
}	t_minimap;

typedef struct s_map
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	t_scene			*r_scene;
	uint32_t		x_offset;
	uint32_t		y_offset;
	float			block_size;
	bool			enabled;
}	t_map;

typedef struct s_scalable
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	float			scale;
}	t_scalable;

typedef struct s_menu
{
	t_scalable		background;
	t_scalable		highlight;
	t_scalable		buttons[2];
	size_t			selection;
	uint32_t		buttons_x_offset;
	uint32_t		buttons_y_offset;
	uint32_t		buttons_y_margin;
}	t_menu;

typedef struct s_window
{
	mlx_t			*mlx;
	enum e_view		view;
	t_scene			scene;
	t_minimap		minimap;
	t_map			map;
	t_menu			menu;
	mlx_image_t		*fps;
}	t_window;

typedef void	(mlx_hook)(void *);
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_close)(void *);
typedef void	(mlx_mouse)(mouse_key_t, action_t, modifier_key_t, void *);
typedef void	(mlx_cursor)(double, double, void *);
typedef void	(mlx_resize)(uint32_t, uint32_t, void *);
typedef void	(mlx_scroll)(double, double, void *);

#endif