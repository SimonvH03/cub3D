/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ammo_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:22:30 by ferid             #+#    #+#             */
/*   Updated: 2025/01/26 13:48:16 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
    draw_number(
        t_scene *scene,
        int number,
        int x_offset)
{
    mlx_texture_t *texture;
    uint32_t x;
    uint32_t y;
    uint32_t color;

    texture = scene->ammo_display.number_textures[number];
    y = 0;
    while (y < texture->height)
    {
        x = 0;
        while (x < texture->width)
        {
            color = get_ray_pixel_colour(texture, x, y);
            if (color != 0)
                mlx_put_pixel(scene->ammo_display.image, x + x_offset, y, color);
            x++;
        }
        y++;
    }
}

static void
    draw_slash(
        t_scene *scene)
{
    mlx_texture_t *texture;
    uint32_t x;
    uint32_t y;
    uint32_t color;
    uint32_t y_offset;

    texture = scene->ammo_display.slash_texture;
    y_offset = (scene->ammo_display.number_textures[0]->height - texture->height) / 2;
    
    y = 0;
    while (y < texture->height)
    {
        x = 0;
        while (x < texture->width)
        {
            color = get_ray_pixel_colour(texture, x, y);
            if (color != 0)
                mlx_put_pixel(scene->ammo_display.image, x + 115, y + y_offset, color);
            x++;
        }
        y++;
    }
}

void
    draw_ammo_display(
        t_scene *scene)
{
    int current_ammo;
    int max_ammo;

    reset_image(scene->ammo_display.image);
    current_ammo = scene->weapon.ammo_count;
    max_ammo = MAX_AMMO;
    draw_number(scene, current_ammo / 10, 50);
    draw_number(scene, current_ammo % 10, 80);
    draw_slash(scene);
    draw_number(scene, max_ammo / 10, 135);
    draw_number(scene, max_ammo % 10, 165);
    scene->ammo_display.image->enabled = true;
    scene->ammo_display.image->instances[0].z = 1;
} 