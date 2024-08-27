/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 15:43:54 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3d_H
# define cub3d_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.14159265358979

// mlx window
# define WINDOW_TITLE "cub3d"
# define WIDTH 50
# define HEIGHT 20

// camera defaults
# define MOVEMENT_SPEED 1
# define ROTATION_SPEED 1
# define CAMERA_PLANE 1

// typedef struct s_precalc
// {
// 	float			a_cos;
// 	float			a_sin;
// 	int				sign;
// 	bool			reproject;
// }	t_precalc;

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
	int				movement_speed;
	int				rotation_speed;
}	t_camera;

// free: scene->map
typedef struct s_scene
{
	char			*name;
	int				fd;
	int				**map;
	int				y_max;
	int				x_max;
	t_camera		*camera;
	int				north_texture;
	int				east_texture;
	int				south_texture;
	int				west_texture;
	uint32_t		floor;
	uint32_t		ceiling;
}	t_scene;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_scene			*scene;
	bool			redraw;
	// t_precalc		precalc;
}	t_cub3d;

//// PHASE 0: function types
// function type undefined by MLX42
typedef void	(mlx_hook)(void *param);
// because 'mlx_scrollfunc' would force all declarations 4 to the right, L norm
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_scroll)(double, double, void *);

//// PHASE 1: initialising mlx window, scene and camera
short		cub3d_init(t_cub3d *cub3d, t_scene *scene, t_camera *camera, char *cub);
short		map_read(t_scene *scene);
void		pov_init(t_camera *camera, int x, int y, char direction);
// void		hud_draw(t_cub3d *cub3d);

//// PHASE 2: interpreting user input to change camera
mlx_hook	user_inputs;
mlx_key		keyhook;
mlx_scroll	scrollhook;

//// PHASE 3: modifying the raycast data based on camera
mlx_hook	raycast;

//// PHASE 4: drawing the raycast
mlx_hook	draw;
//// UTILS
// scene
int			scene_free(t_scene *scene);
// draw
void		draw_background(mlx_image_t *image, t_scene *scene);
// calc
float		deg_to_rad(float angle_deg);
float		ft_abs_float(float val);
short		ft_sign_float(float val);

#endif