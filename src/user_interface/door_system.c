/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

#define DOOR_ANIMATION_SPEED 2.0f
#define DOOR_INTERACTION_RANGE 1.5f
#define DOOR_ANIMATION_STEP 0.016f

static int
	count_doors(
		t_scene *scene)
{
	int x;
	int y;
	int count;

	count = 0;
	y = 0;
	while (y < scene->y_max)
	{
		x = 0;
		while (x < scene->x_max)
		{
			if (scene->map[y][x] == TILE_DOOR)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void
	init_door_state(
		t_door_state *door,
		int x,
		int y)
{
	door->is_opening = false;
	door->is_closing = false;
	door->animation_progress = 0.0f;
	door->animation_speed = DOOR_ANIMATION_SPEED;
	door->x = x;
	door->y = y;
}

static void
	init_all_doors(
		t_scene *scene)
{
	int x;
	int y;
	int count;

	count = 0;
	y = 0;
	while (y < scene->y_max)
	{
		x = 0;
		while (x < scene->x_max)
		{
			if (scene->map[y][x] == TILE_DOOR)
			{
				init_door_state(&scene->doors[count], x, y);
				count++;
			}
			x++;
		}
		y++;
	}
}

void
	init_door_manager(
		t_scene *scene)
{
	int door_count;

	door_count = count_doors(scene);
	scene->doors = malloc(sizeof(t_door_state) * door_count);
	if (!scene->doors)
		return ;
	scene->door_count = door_count;
	scene->max_doors = door_count;
	init_all_doors(scene);
}

bool
	is_door(
		int tile)
{
	return (tile == TILE_DOOR || tile == TILE_DOOR_OPEN);
}

bool
	is_solid(
		int tile)
{
	return (tile == TILE_WALL || tile == TILE_DOOR);
}

t_door_state
	*get_door_at_position(
		t_scene *scene,
		int x,
		int y)
{
	int i;

	i = 0;
	while (i < scene->door_count)
	{
		if (scene->doors[i].x == x && 
			scene->doors[i].y == y)
		{
			return (&scene->doors[i]);
		}
		i++;
	}
	return (NULL);
}

void
	cleanup_door_manager(
		t_scene *scene)
{
	if (scene->doors)
	{
		free(scene->doors);
		scene->doors = NULL;
	}
	scene->door_count = 0;
	scene->max_doors = 0;
}

/*
** Handle door interaction when player presses 'E'
** Checks if there's a door in front of the player and toggles its state
*/
void
	interact_with_door(
		t_scene *scene,
		t_camera *camera)
{
	int		check_x;
	int		check_y;
	float	check_distance;
	float	step;
	t_door_state *door;

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
				// Don't interact if door is in motion
				if (door->is_opening || door->is_closing)
					return;
					
				// Start animation based on current state
				if (scene->map[check_y][check_x] == TILE_DOOR)
				{
					door->is_opening = true;
					door->is_closing = false;
					door->animation_progress = 0.0f;  // Start from closed
				}
				else if (scene->map[check_y][check_x] == TILE_DOOR_OPEN)
				{
					door->is_closing = true;
					door->is_opening = false;
					door->animation_progress = 1.0f;  // Start from open
				}
				scene->recast = true;
			}
			return;
		}
		check_distance += step;
	}
}

void
	update_door_animations(
		t_scene *scene,
		float delta_time)
{
	int x;
	int y;
	t_door_state *door;
	float animation_speed;

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
					{
						door->animation_progress += delta_time * animation_speed;
						if (door->animation_progress >= 1.0f)
						{
							door->animation_progress = 1.0f;
							door->is_opening = false;
							scene->map[y][x] = TILE_DOOR_OPEN;
						}
						scene->recast = true;
					}
					else if (door->is_closing)
					{
						door->animation_progress -= delta_time * animation_speed;
						if (door->animation_progress <= 0.0f)
						{
							door->animation_progress = 0.0f;
							door->is_closing = false;
							scene->map[y][x] = TILE_DOOR;
						}
						scene->recast = true;
					}
				}
			}
			x++;
		}
		y++;
	}
} 