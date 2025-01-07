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

	step = 0.1;
	check_distance = 0.1;
	while (check_distance <= 1.0)
	{
		check_x = (int)(camera->pos_x + camera->dir_x * check_distance);
		check_y = (int)(camera->pos_y + camera->dir_y * check_distance);
		
		if (is_door(scene->map[check_y][check_x]))
		{
			// Toggle door state directly in the map
			scene->map[check_y][check_x] = (scene->map[check_y][check_x] == TILE_DOOR) 
				? TILE_DOOR_OPEN : TILE_DOOR;
			scene->recast = true;
			return;
		}
		check_distance += step;
	}
} 