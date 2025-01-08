/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:12:48 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Initialize a sprite with the given parameters
*/
void
	init_sprite(
		t_sprite_data *sprite,
		enum e_sprite_type type,
		float x,
		float y)
{
	xpm_t *xpm;

	sprite->x = x;
	sprite->y = y;
	sprite->type = type;
	sprite->state = ANIM_IDLE;
	sprite->anim_timer = 0.0f;
	sprite->current_frame = FRAME_DOOR_CLOSED;
	sprite->recast = false;

	// Initialize frames
	if (type == SPR_DOOR_NORMAL)
	{
		// Load door frames with different textures for animation
		xpm = mlx_load_xpm42(DOOR_TEXTURE_PATH);
		sprite->frames[FRAME_DOOR_CLOSED].texture = xpm ? &xpm->texture : NULL;

		xpm = mlx_load_xpm42("./scenes/textures/flag_usa.xpm42");
		sprite->frames[FRAME_DOOR_AJAR].texture = xpm ? &xpm->texture : NULL;

		xpm = mlx_load_xpm42("./scenes/textures/flag_soviet.xpm42");
		sprite->frames[FRAME_DOOR_HALF].texture = xpm ? &xpm->texture : NULL;

		xpm = mlx_load_xpm42("./scenes/textures/flag_nazi.xpm42");
		sprite->frames[FRAME_DOOR_FULL].texture = xpm ? &xpm->texture : NULL;

		// Check if any texture failed to load
		if (!sprite->frames[FRAME_DOOR_CLOSED].texture || !sprite->frames[FRAME_DOOR_AJAR].texture
			|| !sprite->frames[FRAME_DOOR_HALF].texture || !sprite->frames[FRAME_DOOR_FULL].texture)
			error_exit(MLX_INVXPM, EINVAL, "Failed to load door frame textures");
	}
}

/*
** Initialize all sprites in the scene
*/
void
	init_sprites(
		t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->active_sprites)
	{
		// Initialize each sprite based on its type
		init_sprite(&scene->sprites[i], SPR_DOOR_NORMAL, 0, 0);
		i++;
	}
}

void	init_door_frames(t_sprite_data *sprite)
{
	xpm_t			*xpm;

	xpm = mlx_load_xpm42(DOOR_TEXTURE_PATH);
	sprite->frames[FRAME_DOOR_CLOSED].texture = xpm ? &xpm->texture : NULL;

	xpm = mlx_load_xpm42("./scenes/textures/flag_usa.xpm42");
	sprite->frames[FRAME_DOOR_AJAR].texture = xpm ? &xpm->texture : NULL;

	xpm = mlx_load_xpm42("./scenes/textures/flag_soviet.xpm42");
	sprite->frames[FRAME_DOOR_HALF].texture = xpm ? &xpm->texture : NULL;

	xpm = mlx_load_xpm42("./scenes/textures/flag_nazi.xpm42");
	sprite->frames[FRAME_DOOR_FULL].texture = xpm ? &xpm->texture : NULL;

	if (!sprite->frames[FRAME_DOOR_CLOSED].texture || !sprite->frames[FRAME_DOOR_AJAR].texture
		|| !sprite->frames[FRAME_DOOR_HALF].texture || !sprite->frames[FRAME_DOOR_FULL].texture)
		error_exit(MLX_INVXPM, EINVAL, "Failed to load door frame textures");
	sprite->state = ANIM_IDLE;
	sprite->current_frame = FRAME_DOOR_CLOSED;
	sprite->anim_timer = 0.0f;
} 