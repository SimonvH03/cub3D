/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/04/19 00:48:15 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H
# include "MLX42/MLX42_Int.h"
# include "gamestate.h"
# include "paths.h"

# define HUD_FULL_WIDTH		100
# define HUD_FULL_HEIGHT	30
# define HEALTHBAR_WIDTH	30
# define HEALTHBAR_HEIGHT	5
# define AMMO_WIDTH			20
# define CROSSHAIR_SIZE		15

enum	e_window_view
{
	wv_menu,
	wv_game
};

typedef struct s_menu
{
	t_scalable		background;
	t_scalable		highlight;
	t_scalable		buttons[MENU_B_COUNT];
	size_t			selection;
	uint32_t		buttons_x_offset;
	uint32_t		buttons_y_offset;
	uint32_t		buttons_y_margin;
}	t_menu;

typedef struct s_minimap
{
	t_camera		*r_camera;
	t_grid			*r_grid;
	mlx_image_t		*walls;
	uint8_t			*circle_overlay;
	t_scalable		player;
	uint32_t		side;
	uint32_t		radius;
	float			block_size;
}	t_minimap;

typedef struct s_bigmap
{
	t_camera		*r_camera;
	t_grid			*r_grid;
	mlx_image_t		*walls;
	mlx_image_t		*player;
	t_scalable		player_icon_src;
	uint32_t		x_offset;
	uint32_t		y_offset;
	float			block_size;
}	t_bigmap;

typedef struct s_fps
{
	mlx_image_t		*image;
	double			cum_time;
	uint32_t		no_frames;
}	t_fps;

typedef struct s_hud
{
	mlx_texture_t	*player;
	t_fps			fps;
	t_bigmap		bigmap;
	t_minimap		minimap;
}	t_hud;

#endif