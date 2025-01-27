/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:25:00 by ferid             #+#    #+#             */
/*   Updated: 2025/01/27 17:16:23 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static mlx_image_t *ammo_display_image = NULL;

static void
    init_ammo_display_image(
        t_window *window)
{
    if (ammo_display_image == NULL)
    {
        ammo_display_image = mlx_new_image(window->mlx, 200, 50);
        if (!ammo_display_image)
            return;
        if (mlx_image_to_window(window->mlx, ammo_display_image, 
            WIDTH - 200, 35) < 0)
            return;
        ammo_display_image->instances[0].z = 2;
    }
    reset_image(ammo_display_image);
}

static char *
    create_number_texture_path(
        int number)
{
    char    *texture_path;
    char    *number_str;

    number_str = ft_itoa(number);
    if (!number_str)
        return (NULL);
    texture_path = ft_strjoin("scenes/textures/numbers/", number_str);
    free(number_str);
    if (!texture_path)
        return (NULL);
    number_str = texture_path;
    texture_path = ft_strjoin(texture_path, ".xpm42");
    free(number_str);
    return (texture_path);
}

static xpm_t *
    load_number_texture(
        int number)
{
    char    *texture_path;
    xpm_t   *number_xpm;

    texture_path = create_number_texture_path(number);
    if (!texture_path)
        return (NULL);
    number_xpm = mlx_load_xpm42(texture_path);
    free(texture_path);
    return (number_xpm);
}

static void
    draw_texture_to_image(
        xpm_t *texture,
        int x_pos,
        int y_pos)
{
    uint32_t    x;
    uint32_t    y;
    uint32_t    color;

    y = 0;
    while (y < texture->texture.height)
    {
        x = 0;
        while (x < texture->texture.width)
        {
            color = get_ray_pixel_colour(&texture->texture, x, y);
            if (color != 0)
                mlx_put_pixel(ammo_display_image, x + x_pos, y + y_pos, color);
            x++;
        }
        y++;
    }
}

static void
    draw_number(
        int number,
        int x_pos,
        int y_pos)
{
    xpm_t   *number_xpm;

    number_xpm = load_number_texture(number);
    if (!number_xpm)
        return;
    draw_texture_to_image(number_xpm, x_pos, y_pos);
    mlx_delete_xpm42(number_xpm);
}

static void
    draw_slash(
        int x_pos,
        int y_pos)
{
    uint32_t    x;
    uint32_t    y;
    uint32_t    color;
    xpm_t       *slash_xpm;

    slash_xpm = mlx_load_xpm42("scenes/textures/numbers/sl.xpm42");
    if (!slash_xpm)
        return;

    y = 0;
    while (y < slash_xpm->texture.height)
    {
        x = 0;
        while (x < slash_xpm->texture.width)
        {
            color = get_ray_pixel_colour(&slash_xpm->texture, x, y);
            if (color != 0)
                mlx_put_pixel(ammo_display_image, x + x_pos, y + y_pos, color);
            x++;
        }
        y++;
    }
    mlx_delete_xpm42(slash_xpm);
}

void
    draw_ammo_count(
        t_scene *scene)
{
    t_window *window;
    int current_ammo;
    int x_offset;

    window = (t_window *)((char *)scene - offsetof(t_window, scene));
    init_ammo_display_image(window);
    if (!ammo_display_image)
        return;
    current_ammo = scene->weapon.ammo_count;
    if (current_ammo < 10)
    {
        draw_number(0, 15, 5);
        draw_number(current_ammo, 40, 5);
    }
    else
    {
        draw_number(current_ammo / 10, 15, 5);
        draw_number(current_ammo % 10, 40, 5);
    }
    draw_slash(70, 17);
    x_offset = 0;
    if (MAX_AMMO / 10 == 1)
        x_offset = -5;
    draw_number(MAX_AMMO / 10, 85 + x_offset, 5);
    draw_number(MAX_AMMO % 10, 110 + x_offset, 5);
} 