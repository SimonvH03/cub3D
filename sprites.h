#ifndef SPRITES_H
# define SPRITES_H

# include "MLX42/include/MLX42/MLX42.h"

// Sprite types
enum e_sprite_type
{
	SPR_DOOR_NORMAL,
	SPR_DOOR_METAL,
	SPR_COUNT  // Used to allocate arrays
};

// Animation states
enum e_anim_state
{
	ANIM_IDLE,
	ANIM_OPENING,
	ANIM_CLOSING,
	ANIM_COUNT
};

// Frame indices for each sprite type
enum e_frame_index
{
	FRAME_DOOR_CLOSED,
	FRAME_DOOR_AJAR,
	FRAME_DOOR_HALF,
	FRAME_DOOR_FULL,
	FRAME_COUNT
};

// Data for a single animation frame
typedef struct s_frame_data
{
	mlx_texture_t	*texture;
	float			duration;
}	t_frame_data;

// Data for a sprite type, including all its frames
typedef struct s_sprite_data
{
	t_frame_data		frames[FRAME_COUNT];
	enum e_anim_state	state;
	float				anim_timer;
	int					current_frame;
	float				x;
	float				y;
	bool				recast;  // Flag to indicate frame change
}	t_sprite_data;

#endif 