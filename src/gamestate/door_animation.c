/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_animation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 01:08:05 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_door_opening(
		t_door *door,
		float shift)
{
	door->position -= shift;
	if (door->position <= 0.0f)
	{
		door->position = 0.0f;
		door->state = ds_open;
		*door->r_cell &= ~SOLID_MASK;
	}
}

static void
	update_door_closing(
		t_door *door,
		float shift)
{
	door->position += shift;
	if (door->position >= 1.0f)
	{
		door->position = 1.0f;
		door->state = ds_closed;
	}
}

void
	update_doors(
		t_grid *grid,
		float delta_time)
{
	unsigned int	index;
	t_door			*door;

	index = 0;
	while (index < grid->door_count)
	{
		door = &grid->door_list[index];
		if (door->state == ds_opening)
			update_door_opening(door, DOOR_SHIFT_SPEED * delta_time);
		else if (door->state == ds_closing)
			update_door_closing(door, DOOR_SHIFT_SPEED * delta_time);
		index++;
	}
}

void
	operate_door(
		t_door *door,
		t_camera *camera)
{
	if (door->state == ds_closed || door->state == ds_closing)
	{
		door->state = ds_opening;
	}
	else if (door->state == ds_open || door->state == ds_opening)
	{
		if (door->pos_y == (unsigned int)camera->pos_y
			&& door->pos_x == (unsigned int)camera->pos_x)
			return ;
		door->state = ds_closing;
		*door->r_cell |= SOLID_MASK;
	}
}
