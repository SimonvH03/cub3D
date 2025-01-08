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

/*
** Get or create a door state at the given position
*/
t_door_state*
	get_door_at_position(
		t_scene *scene,
		int x,
		int y)
{
	int i;

	// Look for existing door state
	for (i = 0; i < scene->door_count; i++)
	{
		if (scene->doors[i].x == x && scene->doors[i].y == y)
			return &scene->doors[i];
	}

	// Create new door state if not found
	scene->doors = realloc(scene->doors, (scene->door_count + 1) * sizeof(t_door_state));
	if (!scene->doors)
		return NULL;

	scene->doors[scene->door_count].x = x;
	scene->doors[scene->door_count].y = y;
	scene->doors[scene->door_count].is_opening = false;
	scene->doors[scene->door_count].animation_progress = 0.0f;
	
	return &scene->doors[scene->door_count++];
}

/*
** Initialize a single door at the given coordinates
*/
void
	init_door(
		t_scene *scene,
		int x,
		int y)
{
	t_door_state *door;

	scene->map[y][x] = TILE_DOOR;
	door = get_door_at_position(scene, x, y);
	if (door)
	{
		door->is_opening = false;
		door->animation_progress = 0.0f;
	}
}

/*
** Check if a tile is a door (either open or closed)
*/
bool
	is_door(
		int tile)
{
	return (tile == TILE_DOOR || tile == TILE_DOOR_OPEN);
}

/*
** Check if a tile blocks movement (walls and closed doors)
*/
bool
	is_solid(
		int tile)
{
	return (tile == TILE_WALL || tile == TILE_DOOR);  // Only closed doors block movement
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
		
		// Debug output
		printf("Checking position: (%d, %d), Map value: %d\n", 
			check_x, check_y, scene->map[check_y][check_x]);
		
		if (is_door(scene->map[check_y][check_x]))
		{
			printf("Found door at: (%d, %d)\n", check_x, check_y);
			door = get_door_at_position(scene, check_x, check_y);
			if (door)
			{
				printf("Door state - Opening: %d, Progress: %f\n", 
					door->is_opening, door->animation_progress);
				
				// Start animation based on current state
				if (scene->map[check_y][check_x] == TILE_DOOR)
				{
					door->is_opening = true;
					door->animation_progress = 0.0f;  // Start from closed
					printf("Starting door opening animation\n");
				}
				else
				{
					door->is_opening = false;
					door->animation_progress = 1.0f;  // Start from open
					printf("Starting door closing animation\n");
				}
				scene->recast = true;
			}
			else
			{
				printf("Failed to get door state\n");
			}
			return;
		}
		check_distance += step;
	}
	printf("No door found in range\n");
}

/*
** Add a new function to update door animations
*/
void
	update_door_animations(
		t_scene *scene,
		float delta_time)
{
	int x, y;
	t_door_state *door;
	float animation_speed = 1.5f;  // Slightly slower for smoother animation

	for (y = 0; y < scene->height; y++)
	{
		for (x = 0; x < scene->width; x++)
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
							scene->map[y][x] = TILE_DOOR_OPEN;
						}
						scene->recast = true;
					}
					else
					{
						door->animation_progress -= delta_time * animation_speed;
						if (door->animation_progress <= 0.0f)
						{
							door->animation_progress = 0.0f;
							scene->map[y][x] = TILE_DOOR;
						}
						scene->recast = true;
					}
				}
			}
		}
	}
} 