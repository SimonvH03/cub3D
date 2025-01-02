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
	return (tile == TILE_WALL || tile == TILE_DOOR);
}

/*
** Initialize the door system by finding all doors in the map
** and setting up the door tracking structures
*/
void
	init_doors(
		t_scene *scene)
{
	int	x;
	int	y;
	int	capacity;

	capacity = scene->x_max * scene->y_max;
	scene->doors.doors = ft_calloc(capacity, sizeof(t_door));
	scene->doors.capacity = capacity;
	scene->doors.count = 0;
	y = 0;
	while (y < scene->y_max)
	{
		x = 0;
		while (x < scene->x_max)
		{
			if (scene->map[y][x] == TILE_DOOR)
			{
				scene->doors.doors[scene->doors.count].x = x;
				scene->doors.doors[scene->doors.count].y = y;
				scene->doors.doors[scene->doors.count].is_open = false;
				scene->doors.count++;
			}
			x++;
		}
		y++;
	}
}

/*
** Find a door at the specified coordinates
** Returns NULL if no door is found
*/
static t_door
	*find_door(
		t_scene *scene,
		int x,
		int y)
{
	int	i;

	i = 0;
	while (i < scene->doors.count)
	{
		if (scene->doors.doors[i].x == x && scene->doors.doors[i].y == y)
			return (&scene->doors.doors[i]);
		i++;
	}
	return (NULL);
}

/*
** Handle door interaction when player presses 'E'
** Checks if there's a door in front of the player and opens it
*/
void
	interact_with_door(
		t_scene *scene,
		t_camera *camera)
{
	int		check_x;
	int		check_y;
	t_door	*door;
	float	check_distance;
	float	step;

	// Check multiple distances in front of the player
	step = 0.1;
	check_distance = 0.1;
	while (check_distance <= 1.0)
	{
		check_x = (int)(camera->pos_x + camera->dir_x * check_distance);
		check_y = (int)(camera->pos_y + camera->dir_y * check_distance);
		
		// Debug output
		printf("Checking position: (%d, %d), Tile type: %d\n", check_x, check_y, scene->map[check_y][check_x]);
		
		if (is_door(scene->map[check_y][check_x]))
		{
			door = find_door(scene, check_x, check_y);
			if (door)
			{
				// Toggle door state
				door->is_open = !door->is_open;
				scene->map[check_y][check_x] = door->is_open ? TILE_DOOR_OPEN : TILE_DOOR;
				scene->recast = true;
				printf("Door %s at (%d, %d)\n", door->is_open ? "opened" : "closed", check_x, check_y);
				return;
			}
		}
		check_distance += step;
	}
	printf("No door found in range\n");
} 