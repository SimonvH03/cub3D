#ifndef SPRITES_H
# define SPRITES_H

# include "MLX42/include/MLX42/MLX42.h"

// Map tile types and states (matching defs.h)
enum e_tile_type
{
	TILE_EMPTY = 0,
	TILE_WALL,
	TILE_DOOR,
	TILE_DOOR_OPEN
};

// Door state structure (matching defs.h)
typedef struct s_door_state
{
	bool	is_opening;			//	Whether the door is currently opening
	float	animation_progress;	// 0.0 (closed) to 1.0 (open)
	int		x;					// Door position
	int		y;					// Door position
}	t_door;

#endif