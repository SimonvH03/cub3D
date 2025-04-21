/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 23:20:34 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H
# include "MLX42/MLX42.h"
# include "gamestate.h"
# include "player.h"
# include "paths.h"

// UI colours 0xAaBbGgRr
# define C_TRANSPARENT		0x00000000
# define C_TRANSLUCENT		0x42000000
# define C_CEILING			0xBB000000
# define C_FLOOR			0x80424242
# define C_WALL				0xFF2A66C0
# define C_DOOR				0xFF153360
# define C_OPENDOOR			0xFF00C0C0
# define C_ERROR			0xFF80FF00

// uhhhh it wasn't public info for some reason
# define MLX_FONT_WIDTH		10

# define MINIMAP_SCALE		10

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