/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void
	update_ray_position(
		t_ray *ray)
{
	if (ray->total_x < ray->total_y)
	{
		ray->total_x += ray->step_x;
		ray->pos_x += ray->sign_x;
		ray->hit_type = HORIZONTAL;
		ray->distance = ray->total_x - ray->step_x;
	}
	else
	{
		ray->total_y += ray->step_y;
		ray->pos_y += ray->sign_y;
		ray->hit_type = VERTICAL;
		ray->distance = ray->total_y - ray->step_y;
	}
}

void
	update_final_ray_position(
		t_ray *ray)
{
	if (ray->has_door
		&& (!ray->has_wall || ray->door_hit.distance < ray->wall_hit.distance))
	{
		ray->pos_x = ray->door_hit.pos_x;
		ray->pos_y = ray->door_hit.pos_y;
		ray->distance = ray->door_hit.distance;
		ray->hit_type = ray->door_hit.hit_type;
	}
	else if (ray->has_wall)
	{
		ray->pos_x = ray->wall_hit.pos_x;
		ray->pos_y = ray->wall_hit.pos_y;
		ray->distance = ray->wall_hit.distance;
		ray->hit_type = ray->wall_hit.hit_type;
	}
}

bool
	check_wall_hit(
		t_ray *ray,
		t_scene *scene)
{
	if (scene->map[ray->pos_y][ray->pos_x] == TILE_WALL
		|| (scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR
		&& (!get_door_at_position(scene, ray->pos_x, ray->pos_y)
		|| get_door_at_position(scene, ray->pos_x, ray->pos_y)->animation_progress == 0.0f)))
	{
		ray->wall_hit.pos_x = ray->pos_x;
		ray->wall_hit.pos_y = ray->pos_y;
		ray->wall_hit.distance = ray->distance;
		ray->wall_hit.hit_type = ray->hit_type;
		ray->wall_hit.is_door = false;
		ray->has_wall = true;
		return (true);
	}
	return (false);
}

void
	check_door_hit(
		t_ray *ray,
		t_scene *scene)
{
	t_door	*door_state;
	float	door_pos;

	if (ray->has_door || (scene->map[ray->pos_y][ray->pos_x] != TILE_DOOR
		&& scene->map[ray->pos_y][ray->pos_x] != TILE_DOOR_OPEN))
		return ;

	door_state = get_door_at_position(scene, ray->pos_x, ray->pos_y);
	if (!door_state || door_state->animation_progress == 0.0f)
		return ;

	if (ray->hit_type == HORIZONTAL)
		door_pos = scene->camera.pos_y + ray->distance * ray->dir_y;
	else
		door_pos = scene->camera.pos_x + ray->distance * ray->dir_x;
	door_pos -= (int)door_pos;

	ray->door_hit.pos_x = ray->pos_x;
	ray->door_hit.pos_y = ray->pos_y;
	ray->door_hit.distance = ray->distance;
	ray->door_hit.hit_type = ray->hit_type;
	ray->door_hit.is_door = true;
	ray->door_hit.door_state = door_state;

	if (door_pos < (1.0f - door_state->animation_progress))
		ray->has_door = true;
}

void
	cast_ray(
		t_ray *ray,
		t_scene *scene)
{
	ray->has_door = false;
	ray->has_wall = false;

	while (ray->pos_x && ray->pos_x < scene->x_max
		&& ray->pos_y && ray->pos_y < scene->y_max)
	{
		update_ray_position(ray);
		if (check_wall_hit(ray, scene))
			break ;
		check_door_hit(ray, scene);
	}
	update_final_ray_position(ray);
}
