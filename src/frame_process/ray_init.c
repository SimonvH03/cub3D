/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void
    init_ray(
        t_ray *ray,
        t_camera *camera)
{
    ray->pos_x = (int)camera->pos_x;
    ray->pos_y = (int)camera->pos_y;
    ray->dir_x = camera->dir_x + camera->plane_x * 0.5 * ray->camera_x;
    ray->dir_y = camera->dir_y + camera->plane_y * 0.5 * ray->camera_x;
    ray->step_x = ft_abs_float(1 / ray->dir_x);
    if (ray->step_x == INFINITY)
        ray->step_x = UINT32_MAX;
    ray->step_y = ft_abs_float(1 / ray->dir_y);
    if (ray->step_y == INFINITY)
        ray->step_y = UINT32_MAX;
    ray->sign_x = ft_sign_float(ray->dir_x);
    ray->sign_y = ft_sign_float(ray->dir_y);
    if (ray->sign_x > 0)
        ray->total_x = ((ray->pos_x + 1 - camera->pos_x) * ray->step_x);
    else
        ray->total_x = (camera->pos_x - ray->pos_x) * ray->step_x;
    if (ray->sign_y > 0)
        ray->total_y = ((ray->pos_y + 1 - camera->pos_y) * ray->step_y);
    else
        ray->total_y = (camera->pos_y - ray->pos_y) * ray->step_y;
    ray->distance = 0;
}

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
    if (ray->has_door && (!ray->has_wall || ray->door_hit.distance < ray->wall_hit.distance))
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

void
    draw_raycast(
        t_scene *scene)
{
    t_ray   ray;
    uint32_t    x;

    reset_image(scene->walls);
    x = 0;
    while (x < scene->walls->width)
    {
        ray.camera_x = 2 * x / (float)scene->walls->width - 1;
        init_ray(&ray, &scene->camera);
        cast_ray(&ray, scene);
        draw_texture_column(scene, &ray, x);
        ++x;
    }
    draw_health_bar(&scene->health_bar);
    draw_weapon(scene);
} 