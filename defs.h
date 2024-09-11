/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/09/11 02:15:35 by simon            ###   ########.fr       */
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

# define PI 3.14159265358979

// mlx window
# define WINDOW_TITLE "cub3d"
# define WIDTH 2560
# define HEIGHT 1080

// (mini)map defaults
# define C_TRANSPARENT 0x00
# define C_TRANSLUCENT 0x42
# define C_CEILING 0x000000BB
# define C_FLOOR 0x42424280
# define C_WALL 0xBF6629FF
# define C_ERROR 0x00FF80FF

// camera defaults
# define MOVEMENT_SPEED 5
# define ROTATION_SPEED 3
// ratio of cube height / width
# define CAMERA_PLANE 1

// menu button selection
enum	e_select
{
	START,
	SETTINGS,
	QUIT
};

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

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

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
}	t_ray;

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

// free: scene->map
typedef struct s_scene
{
	mlx_image_t		*walls;
	mlx_image_t		*background;
	t_camera		camera;
	char			*name;
	char			**content;
	int				**map;
	int				y_max;
	int				x_max;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*player_texture;
	uint32_t		floor;
	uint32_t		ceiling;
	bool			recast;
}	t_scene;

typedef struct s_minimap
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	uint8_t			*circle_overlay;
	t_scene			*scene;
	uint32_t		side;
	uint32_t		radius;
	float			scale;
	bool			enabled;
}	t_minimap;

typedef struct s_map
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	t_scene			*scene;
	uint32_t		width;
	uint32_t		height;
	uint32_t		x_offset;
	uint32_t		y_offset;
	float			scale;
	bool			enabled;
}	t_map;

typedef struct s_menu
{
	mlx_image_t		*background;
	mlx_image_t		*interaction_highlight;
	enum e_select	selection;
	mlx_image_t		*button_start_game;
	mlx_image_t		*button_settings;
	mlx_image_t		*button_quit;
}	t_menu;

typedef struct s_window
{
	mlx_t			*mlx;
	enum e_view		view;
	t_scene			scene;
	t_minimap		minimap;
	t_map			map;
	t_menu			menu;
	float			time;
	float			deltatime;
	mlx_image_t		*fps;
}	t_window;

typedef void	(mlx_hook)(void *param);
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_scroll)(double, double, void *);

#endif