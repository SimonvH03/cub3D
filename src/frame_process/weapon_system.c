/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:45:23 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/01/19 15:45:23 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

short
    init_weapon(
        mlx_t *mlx,
        t_scene *scene)
{
    xpm_t* weapon_xpm;

    weapon_xpm = mlx_load_xpm42("scenes/textures/g1/01.xpm42");
    if (!weapon_xpm)
        return (EXIT_FAILURE);
    scene->weapon.texture = &weapon_xpm->texture;

    // Calculate scaled dimensions to maintain aspect ratio
    uint32_t scaled_width = scene->weapon.texture->width * scene->weapon.scale;
    uint32_t scaled_height = scene->weapon.texture->height * scene->weapon.scale;

    scene->weapon.image = mlx_new_image(mlx, scaled_width, scaled_height);
    if (!scene->weapon.image)
        return (EXIT_FAILURE);

    // Position the weapon at the bottom center of the screen
    scene->weapon.x_pos = (WIDTH - scaled_width) / 2;
    scene->weapon.y_pos = HEIGHT - scaled_height;

    // Create the weapon image
    if (mlx_image_to_window(mlx, scene->weapon.image, 
        scene->weapon.x_pos, scene->weapon.y_pos) < 0)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

void
    draw_weapon(
        t_scene *scene)
{
    uint32_t    x;
    uint32_t    y;
    uint32_t    color;
    const int   pixel_size = 9;

    if (!scene->weapon.enabled)
        return;

    y = 0;
    while (y < scene->weapon.image->height)
    {
        x = 0;
        while (x < scene->weapon.image->width)
        {
            // Sample color from the top-left of each block
            color = get_ray_pixel_colour(scene->weapon.texture, 
                    (x / pixel_size) * pixel_size, 
                    (y / pixel_size) * pixel_size);

            // Fill the entire block with the sampled color
            if ((color & 0xFF) != 0)
            {
                int py = 0;
                while (py < pixel_size && (y + py) < scene->weapon.image->height)
                {
                    int px = 0;
                    while (px < pixel_size && (x + px) < scene->weapon.image->width)
                    {
                        mlx_put_pixel(scene->weapon.image, x + px, y + py, color);
                        px++;
                    }
                    py++;
                }
            }
            x += pixel_size;
        }
        y += pixel_size;
    }
} 