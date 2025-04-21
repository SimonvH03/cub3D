/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gamestate.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 22:47:14 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_H
# define GAMESTATE_H
# include "MLX42/MLX42.h"

typedef struct s_scalable
{
	mlx_image_t			*image;
	mlx_texture_t		*texture;
	float				scale;
}	t_scalable;

// tilemap cell composition
// Solid bit | Axis bit | ID (0-127) | Type (0 - 127)
# define SOLID_SHIFT	15
# define AXIS_SHIFT		14
# define ID_SHIFT		7
# define SOLID_MASK		0x8000
# define AXIS_MASK		0x4000
# define ID_MASK		0x3F80
# define TYPE_MASK		0x007F

// animation
# define DOOR_SHIFT_SPEED	1

// interaction
# define INTERACTION_RANGE	1.5

enum	e_door_state
{
	ds_open,
	ds_closed,
	ds_opening,
	ds_closing
};

typedef struct s_interaction_ray
{
	unsigned int	pos_x;
	unsigned int	pos_y;
	float			dir_x;
	float			dir_y;
	float			step_x;
	float			step_y;
	float			total_x;
	float			total_y;
	float			distance;
	short			sign_x;
	short			sign_y;
}	t_interaction_ray;

typedef struct s_walls
{
	mlx_image_t			*image;
	mlx_texture_t		*north;
	mlx_texture_t		*east;
	mlx_texture_t		*south;
	mlx_texture_t		*west;
	mlx_texture_t		*doorface;
	mlx_texture_t		*doorside;
}	t_walls;

typedef struct s_door
{
	int16_t				*r_cell;
	float				position;
	unsigned int		pos_y;
	unsigned int		pos_x;
	enum e_door_state	state;
}	t_door;

typedef struct s_grid
{
	int16_t				**tilemap;
	t_door				*door_list;
	unsigned int		door_count;
	unsigned int		y_max;
	unsigned int		x_max;
}	t_grid;

typedef struct s_scene
{
	t_walls				walls;
	t_grid				grid;
	uint32_t			floor_clr;
	uint32_t			ceiling_clr;
}	t_scene;

#endif