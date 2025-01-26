/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ammo_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:21:45 by ferid             #+#    #+#             */
/*   Updated: 2025/01/26 13:31:54 by ferid            ###   ########.fr       */
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
        scene->ammo_display.number_textures[i] = &mlx_load_xpm42(texture_path)->texture;
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
    scene->ammo_display.slash_texture = &mlx_load_xpm42("scenes/textures/numbers/sl.xpm42")->texture;
    if (!scene->ammo_display.slash_texture)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static short
    create_ammo_display_image(
        mlx_t *mlx,
        t_scene *scene)
{
    scene->ammo_display.image = mlx_new_image(mlx, 200, 45);
    if (!scene->ammo_display.image)
        return (EXIT_FAILURE);

    scene->ammo_display.x_pos = WIDTH - 250;
    scene->ammo_display.y_pos = 50;

    if (mlx_image_to_window(mlx, scene->ammo_display.image,
        scene->ammo_display.x_pos, scene->ammo_display.y_pos) < 0)
        return (EXIT_FAILURE);

    scene->ammo_display.image->instances[0].z = 1;
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