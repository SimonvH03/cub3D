/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:21:00 by ferid             #+#    #+#             */
/*   Updated: 2025/01/26 13:24:33 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static short
    load_number_textures(
        t_scene *scene)
{
    char    *texture_path;
    char    *number;
    int     i;

    i = 0;
    while (i < 10)
    {
        number = ft_itoa(i);
        if (!number)
            return (EXIT_FAILURE);
        texture_path = ft_strjoin("scenes/textures/numbers/", number);
        free(number);
        if (!texture_path)
            return (EXIT_FAILURE);
        number = texture_path;
        texture_path = ft_strjoin(texture_path, ".xpm42");
        free(number);
        if (!texture_path)
            return (EXIT_FAILURE);
        scene->ammo_display.number_textures[i] = mlx_load_xpm42(texture_path);
        free(texture_path);
        if (!scene->ammo_display.number_textures[i])
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}

static short
    load_slash_texture(
        t_scene *scene)
{
    scene->ammo_display.slash_texture = mlx_load_xpm42("scenes/textures/numbers/sl.xpm42");
    if (!scene->ammo_display.slash_texture)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static short
    create_ammo_display_image(
        mlx_t *mlx,
        t_scene *scene)
{
    scene->ammo_display.image = mlx_new_image(mlx, 100, 45);
    if (!scene->ammo_display.image)
        return (EXIT_FAILURE);

    scene->ammo_display.x_pos = WIDTH - 150;
    scene->ammo_display.y_pos = HEIGHT - 100;

    if (mlx_image_to_window(mlx, scene->ammo_display.image,
        scene->ammo_display.x_pos, scene->ammo_display.y_pos) < 0)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

short
    init_ammo_display(
        mlx_t *mlx,
        t_scene *scene)
{
    if (load_number_textures(scene) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (load_slash_texture(scene) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (create_ammo_display_image(mlx, scene) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

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

    texture = scene->ammo_display.slash_texture;
    y = 0;
    while (y < texture->height)
    {
        x = 0;
        while (x < texture->width)
        {
            color = get_ray_pixel_colour(texture, x, y);
            if (color != 0)
                mlx_put_pixel(scene->ammo_display.image, x + 35, y, color);
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

    // Draw current ammo (left side of slash)
    if (current_ammo < 10)
        draw_number(scene, current_ammo, 15);
    else
    {
        draw_number(scene, current_ammo / 10, 0);
        draw_number(scene, current_ammo % 10, 30);
    }

    // Draw slash
    draw_slash(scene);

    // Draw max ammo (right side of slash)
    draw_number(scene, max_ammo / 10, 55);
    draw_number(scene, max_ammo % 10, 85);
} 