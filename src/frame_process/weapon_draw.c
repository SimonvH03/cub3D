/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:21 by ferid             #+#    #+#             */
/*   Updated: 2025/01/21 17:16:36 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
    draw_weapon_frame(
        t_scene *scene)
{
    uint32_t    x;
    uint32_t    y;
    uint32_t    color;
    const int   pixel_size = 9;

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