/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/08/28 01:39:17 by simon            ###   ########.fr       */
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
# define WIDTH 2560
# define HEIGHT 1440

// scene defaults
# define TILE_SIZE 100
# define C_CEILING 0x000000FF
# define C_FLOOR 0x444444FF
# define C_WALL 0x882222FF

// camera defaults
# define MOVEMENT_SPEED 0.07
# define ROTATION_SPEED 0.03
# define CAMERA_PLANE 0.9

typedef struct s_precalc
{
	double			a_sin;
	double			a_cos;
	int				sign_alpha;
	bool			reproject;
}	t_precalc;

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

typedef struct s_ray
{
	double			dir_y;
	double			dir_x;
	double			step_y;
	double			step_x;
	double			total_y;
	double			total_x;
	short			sign_y;
	short			sign_x;
	int				pos_y;
	int				pos_x;
}	t_ray;

typedef struct s_camera
{
	double			pos_y;
	double			pos_x;
	double			dir_y;
	double			dir_x;
	double			plane_y;
	double			plane_x;
	t_precalc		precalc;
	double			rotation_speed;
	double			movement_speed;
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
void		camera_init(t_camera *camera, int x, int y, char direction);
// void		hud_draw(t_cub3d *cub3d);

//// PHASE 2: interpreting user input to change camera data
mlx_hook	user_inputs;
mlx_key		keyhook;
mlx_scroll	scrollhook;
void		rotate_camera(t_camera *camera);

//// PHASE 4: drawing the raycast
mlx_hook	raycast;
//// UTILS
// scene
int			scene_free(t_scene *scene);
// draw
void		draw_background(mlx_image_t *image, t_scene *scene);
uint32_t	gradient(double ratio, uint32_t end, uint32_t start);
// calc
double		deg_to_rad(double angle_deg);
double		ft_max_double(double a, double b);
double		ft_abs_double(double value);
short		ft_sign_double(double value);
// test
void		print_camera(t_camera *camera);
void		print_map(t_scene *scene);
void		print_ray(t_ray *ray);

#endif