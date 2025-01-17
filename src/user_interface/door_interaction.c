/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	start_door_opening(
		t_door *door,
		t_scene *scene)
{
	door->is_opening = true;
	door->is_closing = false;
	door->animation_progress = 0.0f;
	scene->recast = true;
}

static void
	start_door_closing(
		t_door *door,
		t_scene *scene)
{
	door->is_closing = true;
	door->is_opening = false;
	door->animation_progress = 1.0f;
	scene->recast = true;
}

void
	interact_with_door(
		t_scene *scene,
		t_camera *camera)
{
	int		check_x;
	int		check_y;
	float	check_distance;
	float	step;
	t_door	*door;

	if (is_door(scene->map[(int)camera->pos_y][(int)camera->pos_x]))
		return ;
	step = 0.1;
	check_distance = 0.1;
	while (check_distance <= 1.0)
	{
		check_x = (int)(camera->pos_x + camera->dir_x * check_distance);
		check_y = (int)(camera->pos_y + camera->dir_y * check_distance);
		if (is_door(scene->map[check_y][check_x]))
		{
			door = get_door_at_position(scene, check_x, check_y);
			if (door)
			{
				if (scene->map[check_y][check_x] == TILE_DOOR)
					start_door_opening(door, scene);
				else
					start_door_closing(door, scene);
			}
			return ;
		}
		check_distance += step;
	}
}
