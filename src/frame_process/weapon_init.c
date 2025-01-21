/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:45:23 by svan-hoo          #+#    #+#             */
/*   Updated: 2025/01/21 21:23:57 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
    init_weapon_state(
        t_scene *scene)
{
    int i = 0;
    
    // Initialize all texture pointers to NULL
    while (i < 34)
    {
        scene->weapon.textures[i] = NULL;
        i++;
    }
    
    scene->weapon.current_frame = 0;
    scene->weapon.enabled = true;
    scene->weapon.scale = 1.0;
    scene->weapon.is_animating = false;
    scene->weapon.is_reloading = false;
    scene->weapon.frame_time = 0.0f;
    scene->weapon.frame_delay = 0.1f; // 100ms between frames
}

static short
    load_weapon_textures(
        t_scene *scene)
{
    char texture_path[50];
    xpm_t* weapon_xpm;
    int i;

    i = 0;
    while (i < 34)
    {
        snprintf(texture_path, sizeof(texture_path), "scenes/textures/g1/%02d.xpm42", i + 1);
        weapon_xpm = mlx_load_xpm42(texture_path);
        if (!weapon_xpm)
            return (EXIT_FAILURE);
        scene->weapon.textures[i] = &weapon_xpm->texture;
        i++;
    }
    scene->weapon.texture = scene->weapon.textures[0];
    return (EXIT_SUCCESS);
}

static short
    create_weapon_image(
        mlx_t *mlx,
        t_scene *scene)
{
    uint32_t scaled_width;
    uint32_t scaled_height;

    scaled_width = scene->weapon.texture->width * scene->weapon.scale;
    scaled_height = scene->weapon.texture->height * scene->weapon.scale;

    scene->weapon.image = mlx_new_image(mlx, scaled_width, scaled_height);
    if (!scene->weapon.image)
        return (EXIT_FAILURE);

    scene->weapon.x_pos = (WIDTH - scaled_width) / 2;
    scene->weapon.y_pos = HEIGHT - scaled_height;

    if (mlx_image_to_window(mlx, scene->weapon.image, 
        scene->weapon.x_pos, scene->weapon.y_pos) < 0)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

short
    init_weapon(
        mlx_t *mlx,
        t_scene *scene)
{
    init_weapon_state(scene);
    if (load_weapon_textures(scene) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (create_weapon_image(mlx, scene) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
} 