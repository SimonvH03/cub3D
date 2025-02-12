/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:25:08 by ferid             #+#    #+#             */
/*   Updated: 2025/01/22 23:15:52 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
    clear_weapon_image(
        mlx_image_t *image)
{
    uint32_t    cy;
    uint32_t    cx;

    cy = 0;
    while (cy < image->height)
    {
        cx = 0;
        while (cx < image->width)
        {
            mlx_put_pixel(image, cx, cy, 0x00000000);
            cx++;
        }
        cy++;
    }
}

static void
    draw_pixel_block(
        mlx_image_t *image,
        uint32_t x,
        uint32_t y,
        uint32_t color)
{
    const int   pixel_size = 12;
    uint32_t    cy;
    uint32_t    cx;

    cy = 0;
    while (cy < pixel_size && (y + cy) < image->height)
    {
        cx = 0;
        while (cx < pixel_size && (x + cx) < image->width)
        {
            mlx_put_pixel(image, x + cx, y + cy, color);
            cx++;
        }
        cy++;
    }
}

static void
    draw_weapon_frame(
        t_scene *scene)
{
    uint32_t    x;
    uint32_t    y;
    uint32_t    color;
    float       scale_x;
    float       scale_y;
    const int   pixel_size = 12;

    scale_x = (float)WIDTH / (scene->weapon.texture->width * pixel_size);
    scale_y = (float)HEIGHT / (scene->weapon.texture->height * pixel_size);

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            uint32_t tex_x = (uint32_t)((float)x / scale_x / pixel_size);
            uint32_t tex_y = (uint32_t)((float)y / scale_y / pixel_size); 
            color = get_ray_pixel_colour(scene->weapon.texture, tex_x, tex_y);
            if ((color & 0xFF000000) != 0)
                draw_pixel_block(scene->weapon.image, x, y, color);
            x += pixel_size;
        }
        y += pixel_size;
    }
}

void
    draw_weapon(
        t_scene *scene)
{
    if (!scene->weapon.enabled)
        return;
    clear_weapon_image(scene->weapon.image);
    draw_weapon_frame(scene);
}

void
    draw_crosshair(
        t_scene *scene)
{
    uint32_t    x;
    uint32_t    y;
    uint32_t    color;

    y = 0;
    while (y < scene->crosshair_texture->height)
    {
        x = 0;
        while (x < scene->crosshair_texture->width)
        {
            color = get_ray_pixel_colour(scene->crosshair_texture, x, y);
            if ((color & 0x000000FF) > 0)
                mlx_put_pixel(scene->crosshair, x, y, color);
            x++;
        }
        y++;
    }
} 