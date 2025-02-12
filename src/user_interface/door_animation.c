/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	update_opening_door(
		t_door_state *door,
		t_scene *scene,
		float delta_time,
		float animation_speed)
{
	door->animation_progress += delta_time * animation_speed;
	if (door->animation_progress >= 1.0f)
	{
		door->animation_progress = 1.0f;
		scene->map[door->y][door->x] = TILE_DOOR_OPEN;
	}
	scene->recast = true;
}

static void
	update_closing_door(
		t_door_state *door,
		t_scene *scene,
		float delta_time,
		float animation_speed)
{
	door->animation_progress -= delta_time * animation_speed;
	if (door->animation_progress <= 0.0f)
	{
		door->animation_progress = 0.0f;
		scene->map[door->y][door->x] = TILE_DOOR;
	}
	scene->recast = true;
}

void
	update_door_animations(
		t_scene *scene,
		float delta_time)
{
	int		x;
	int		y;
	t_door_state	*door;
	float	animation_speed;

	animation_speed = 1.5f;
	y = 0;
	while (y < scene->y_max)
	{
		x = 0;
		while (x < scene->x_max)
		{
			if (is_door(scene->map[y][x]))
			{
				door = get_door_at_position(scene, x, y);
				if (door)
				{
					if (door->is_opening)
						update_opening_door(door, scene, delta_time, animation_speed);
					else
						update_closing_door(door, scene, delta_time, animation_speed);
				}
			}
			x++;
		}
		y++;
	}
}
