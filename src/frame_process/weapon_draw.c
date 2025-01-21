/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:25:08 by ferid             #+#    #+#             */
/*   Updated: 2025/01/21 21:31:00 by ferid            ###   ########.fr       */
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
    const int   pixel_size = 12;

    y = 0;
    while (y < scene->weapon.image->height)
    {
        x = 0;
        while (x < scene->weapon.image->width)
        {
            color = get_ray_pixel_colour(scene->weapon.texture, 
                    (x / pixel_size) * pixel_size, 
                    (y / pixel_size) * pixel_size);
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