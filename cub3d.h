/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/28 15:26:42 by svan-hoo         ###   ########.fr       */
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
# define WIDTH 2000
# define HEIGHT 1600

// cub3d defaults
# define DEFAULT_FOV 90
# define ROTATION_SPEED 0.01
# define MOVEMENT_SPEED 1

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

// free: map->content, map->project, map->polar
typedef struct s_map
{
	int				fd;
	char			*name;
}	t_map;

typedef struct s_precalc
{
	short			beta;
	int				sign;
	bool			reproject;
}	t_precalc;

typedef struct s_cosin
{
	double			a_cos;
	double			a_sin;
}	t_cosin;

typedef struct s_pov
{
	int				x;
	int				y;
	int				fov;
	double			direction;

}	t_pov;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*menu_image;
	t_map			*map;
	t_precalc		precalc;
	t_cosin			cosin;
	t_pov			pov;
	bool			redraw;
}	t_cub3d;

//// PHASE 0: function types
// function type used to modify points on a (t_point **) type map
typedef	void	(mapi_func)(void *param, const int y, const int x);
// function type undefined by MLX42
typedef void	(mlx_hook)(void *param);
// because 'mlx_scrollfunc' would force all declarations 4 to the right, L norm
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_scroll)(double, double, void *);

//// PHASE 1: initialising windows, maps and settings based on map
// map
int			map_init(t_map *map, char *map_name);
int			map_read(t_map *map);
mapi_func	map_colour;
// cub3d (mlx window)
int			cub3d_init(t_cub3d *cub3d, t_map *map);
// draw the menu because it's static anyway
void		menu_draw(t_cub3d *cub3d);

//// PHASE 2: interpreting user input to set up point modification
mlx_hook	user_inputs;
mlx_key		keyhook;
mlx_scroll	scrollhook;

// presets for spherical or flat projection
void		input_presets_flat(t_cub3d *cub3d);

//// PHASE 3: modifying the projection data based on interpreted user input
mlx_hook	project;
// Mother of Death, responsible for 9 victims, with some of with her children
// loops over map and applies function with each point's [y][x] coordinates
void		map_iteration(t_map *map, mapi_func *function, void *param);
// MoD's children, the map iteration functions
mapi_func	cub3d_rotate;
mapi_func	cub3d_rotate_optimized;
mapi_func	cub3d_scale;
mapi_func	map_fill_polar;
mapi_func	map_set_polar;
mapi_func	map_set_original;

//// PHASE 4: drawing the cub3d based on the projection data
mlx_hook	draw;
//// UTILS
// map
int			map_free(t_map *map);
int			map_free_err(t_map *map);
// map_read
int			map_calloc_y(t_map *map);
int			map_calloc_x(t_map *map, const int y);
// cub3d
void		cub3d_center_offset(t_cub3d *cub3d);
// draw
void		draw_background(const mlx_image_t *image, const uint32_t colour);
int			draw_check_point(const t_cub3d *cub3d, int x_pixel, int y_pixel);
uint32_t	gradient(double ratio, uint32_t end, uint32_t start);
// calc
double		deg_to_rad(double angle_deg);
double		ft_abs_double(double val);
short		ft_sign_double(double val);

#endif