/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:02:00 by ferid             #+#    #+#             */
/*   Updated: 2024/01/08 12:44:00 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Get current frame index based on animation state and timer
*/
static int
	get_current_frame(
		enum e_anim_state state,
		float timer)
{
	if (state == ANIM_IDLE)
		return (FRAME_DOOR_CLOSED);
	else if (state == ANIM_OPENING)
	{
		if (timer < 0.5f)
			return (FRAME_DOOR_AJAR);
		else if (timer < 1.0f)
			return (FRAME_DOOR_HALF);
		else if (timer < 1.5f)
			return (FRAME_DOOR_FULL);
		return (FRAME_DOOR_FULL);
	}
	else if (state == ANIM_CLOSING)
	{
		if (timer < 0.5f)
			return (FRAME_DOOR_FULL);
		else if (timer < 1.0f)
			return (FRAME_DOOR_HALF);
		else if (timer < 1.5f)
			return (FRAME_DOOR_AJAR);
		return (FRAME_DOOR_CLOSED);
	}
	return (FRAME_DOOR_CLOSED);
}

/*
** Update a single sprite's animation state
*/
static void
	update_sprite_animation(
		t_scene *scene,
		t_sprite_data *sprite,
		float delta_time)
{
	int prev_frame;
	int map_x;
	int map_y;
	t_door_state *door;

	if (sprite->state != ANIM_IDLE)
	{
		prev_frame = sprite->current_frame;
		sprite->anim_timer += delta_time;
		
		sprite->current_frame = get_current_frame(sprite->state, sprite->anim_timer);
		
		if (sprite->anim_timer >= 1.5f)
		{
			map_x = (int)sprite->x;
			map_y = (int)sprite->y;
			
			// Get corresponding door state
			door = get_door_at_position(scene, map_x, map_y);
			if (door)
			{
				if (sprite->state == ANIM_OPENING)
				{
					sprite->current_frame = FRAME_DOOR_FULL;
					scene->map[map_y][map_x] = TILE_DOOR_OPEN;
					door->animation_progress = 1.0f;
				}
				else if (sprite->state == ANIM_CLOSING)
				{
					sprite->current_frame = FRAME_DOOR_CLOSED;
					scene->map[map_y][map_x] = TILE_DOOR;
					door->animation_progress = 0.0f;
				}
			}
				
			sprite->state = ANIM_IDLE;
			sprite->anim_timer = 0;
			scene->recast = true;
		}

		if (prev_frame != sprite->current_frame)
		{
			sprite->recast = true;
			if (door)
			{
				// Update door animation progress based on frame
				switch (sprite->current_frame)
				{
					case FRAME_DOOR_CLOSED:
						door->animation_progress = 0.0f;
						break;
					case FRAME_DOOR_AJAR:
						door->animation_progress = 0.33f;
						break;
					case FRAME_DOOR_HALF:
						door->animation_progress = 0.66f;
						break;
					case FRAME_DOOR_FULL:
						door->animation_progress = 1.0f;
						break;
				}
			}
		}
	}
}

/*
** Update all sprite animations in the scene
*/
void
	update_sprites(
		t_scene *scene,
		float delta_time)
{
	int	i;

	i = 0;
	while (i < scene->active_sprites)
	{
		update_sprite_animation(scene, &scene->sprites[i], delta_time);
		if (scene->sprites[i].recast)
		{
			scene->recast = true;
			scene->sprites[i].recast = false;
		}
		i++;
	}
} 