/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:08 by ferid             #+#    #+#             */
/*   Updated: 2025/01/26 13:17:55 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../cub3d.h"

void
    start_weapon_animation(
        t_scene *scene)
{
    if (!scene->weapon.is_animating && !scene->weapon.is_reloading && scene->weapon.ammo_count > 0) {
        scene->weapon.is_animating = true;
        scene->weapon.current_frame = 0;
        scene->weapon.frame_time = 0.0f;
        scene->weapon.texture = scene->weapon.textures[0];
        scene->weapon.ammo_count--;
        scene->recast = true;
    }
}

void
    start_reload_animation(
        t_scene *scene)
{
    if (!scene->weapon.is_reloading && !scene->weapon.is_animating && scene->weapon.ammo_count < MAX_AMMO) {
        scene->weapon.is_reloading = true;
        scene->weapon.current_frame = 7;
        scene->weapon.frame_time = 0.0f;
        scene->weapon.texture = scene->weapon.textures[7];
        scene->recast = true;
    }
}

void
    next_weapon_frame(
        t_scene *scene,
        float delta_time)
{
    if (!scene->weapon.is_animating && !scene->weapon.is_reloading)
        return;

    scene->weapon.frame_time += delta_time;
    if (scene->weapon.frame_time < scene->weapon.frame_delay)
        return;

    scene->weapon.frame_time = 0.0f;

    if (scene->weapon.is_reloading)
    {
        scene->weapon.current_frame++;
        if (scene->weapon.current_frame >= 34) {
            scene->weapon.current_frame = 0;
            scene->weapon.is_reloading = false;
            scene->weapon.ammo_count = MAX_AMMO;
            scene->weapon.texture = scene->weapon.textures[0];
        }
        else {
            scene->weapon.texture = scene->weapon.textures[scene->weapon.current_frame];
        }
    }
    else if (scene->weapon.is_animating)
    {
        scene->weapon.current_frame++;
        if (scene->weapon.current_frame >= 6) {
            scene->weapon.current_frame = 0;
            scene->weapon.is_animating = false;
        }
        scene->weapon.texture = scene->weapon.textures[scene->weapon.current_frame];
    }
    scene->recast = true;
} 