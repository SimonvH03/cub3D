/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_column_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static mlx_texture_t *
    select_door_texture(
        t_scene *scene,
        t_ray *ray)
{
    if ((ray->hit_type == HORIZONTAL && ray->sign_x > 0) ||  // East
        (ray->hit_type == VERTICAL && ray->sign_y < 0))      // North
        return (scene->door_texture);
    return (scene->door_texture2);                           // South or West
}

static mlx_texture_t *
    select_wall_texture(
        t_scene *scene,
        t_ray *ray)
{
    if (ray->hit_type == HORIZONTAL && ray->sign_x > 0)
        return (scene->east_texture);
    else if (ray->hit_type == HORIZONTAL && ray->sign_x < 0)
        return (scene->west_texture);
    else if (ray->hit_type == VERTICAL && ray->sign_y > 0)
        return (scene->south_texture);
    return (scene->north_texture);
}

static void
    calculate_texture_x(
        t_scene *scene,
        t_ray *ray,
        t_column *column,
        t_door_state *door_state)
{
    if (ray->hit_type == HORIZONTAL)
        column->x = scene->camera.pos_y + ray->distance * ray->dir_y;
    else
        column->x = scene->camera.pos_x + ray->distance * ray->dir_x;
    column->x -= (int)column->x;

    if (door_state)
    {
        if (column->x > (1.0f - door_state->animation_progress))
            column->x = 2.0f;  // Set to invalid value to skip drawing
        else
            column->x += door_state->animation_progress;
    }
}

static void
    calculate_column_dimensions(
        t_scene *scene,
        t_ray *ray,
        t_column *column)
{
    column->height = scene->walls->height / ray->distance;
    column->start = (int)(scene->walls->height - column->height) / 2;
    if (column->start < 0)
        column->start = 0;
    column->end = (scene->walls->height + column->height) / 2;
    if ((uint32_t)column->end >= scene->walls->height)
        column->end = scene->walls->height;
    column->step = column->texture->height / (float)column->height;
    column->y = (column->start - (int)scene->walls->height / 2
            + column->height / 2) * column->step;
}

void
    init_column(
        t_scene *scene,
        t_ray *ray,
        t_column *column)
{
    t_door_state *door_state;

    door_state = NULL;
    if (scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR ||
        scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR_OPEN)
    {
        column->texture = select_door_texture(scene, ray);
        door_state = get_door_at_position(scene, ray->pos_x, ray->pos_y);
    }
    else
        column->texture = select_wall_texture(scene, ray);

    calculate_texture_x(scene, ray, column, door_state);
    calculate_column_dimensions(scene, ray, column);
}
