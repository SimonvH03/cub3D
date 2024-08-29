/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/08/29 23:32:34 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.14159265358979

// mlx window
# define WINDOW_TITLE "cub3d"
# define WIDTH 2560
# define HEIGHT 1440

// minimap defaults
# define C_BORDER 0x80008080
# define C_TRANSPARENT 0xFFFFFF40

// scene defaults
# define TILE_SIZE 100
# define C_CEILING 0x000000FF
# define C_FLOOR 0x383338FF
# define C_WALL 0xBF6629FF

// camera defaults
# define MOVEMENT_SPEED 0.07
# define ROTATION_SPEED 0.03
# define CAMERA_PLANE 0.9

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

typedef struct s_ray
{
	float			dir_y;
	float			dir_x;
	float			step_y;
	float			step_x;
	float			total_y;
	float			total_x;
	short			sign_y;
	short			sign_x;
	int				pos_y;
	int				pos_x;
}	t_ray;

typedef struct s_camera
{
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plane_y;
	float			plane_x;
	float			rm[2];
	short			sign_rotate;
	float			rotation_speed;
	float			movement_speed;
}	t_camera;

typedef struct s_minimap
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	uint8_t			*border_overlay;
	int				**map;
	int				width;
	int				height;
	int				y_offset;
	int				x_offset;
	int				radius;
	int				border_thickness;
}	t_minimap;

// free: scene->map
typedef struct s_scene
{
	mlx_image_t		*walls;
	mlx_image_t		*background;
	t_camera		camera;
	char			*name;
	int				fd;
	int				**map;
	int				y_max;
	int				x_max;
	mlx_texture_t	north_texture;
	mlx_texture_t	east_texture;
	mlx_texture_t	south_texture;
	mlx_texture_t	west_texture;
	uint32_t		floor;
	uint32_t		ceiling;
	bool			recast;
}	t_scene;

typedef struct s_window
{
	mlx_t			*mlx;
	t_scene			scene;
	t_minimap		minimap;
	bool			redraw;
}	t_window;

typedef void	(mlx_hook)(void *param);
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_scroll)(float, float, void *);

#endif