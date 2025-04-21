/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 22:03:57 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "MLX42/MLX42.h"
# include "gamestate.h"

// player defaults
# define MOVEMENT_SPEED		4
# define ROTATION_SPEED		2
# define CURSOR_ROT_SPEED	50
# define COLLISION_HITBOX	0.2

// weapon details
# define G1_MAG_CAPACITY	9
# define G1_SPARE_MAGS		4
# define G1_FRAME_RATE		16

enum	e_weapon_state
{
	ws_idle,
	ws_firing,
	ws_reloading
};

typedef struct s_camera
{
	float				pos_y;
	float				pos_x;
	float				dir_y;
	float				dir_x;
	float				plane_y;
	float				plane_x;
	float				rotation_cosin[2];
	float				movement_matrix[3][3];
	float				movement_speed;
	float				cursor_rot_speed;
	float				aspect_ratio;
	int32_t				height_offset;
}	t_camera;

typedef struct s_weapon
{
	t_scalable			rest;
	t_scalable			*fire;
	t_scalable			*reload;
	mlx_image_t			*display_img;
	uint32_t			mag_capacity;
	uint32_t			total_ammo;
	uint32_t			ammo;
	unsigned int		frame_id;
	float				frame_time;
	float				frame_time_goal;
	enum e_weapon_state	state;
}	t_weapon;

typedef struct s_player
{
	t_camera			camera;
	t_weapon			weapon;
}	t_player;

#endif