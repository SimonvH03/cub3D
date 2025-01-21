/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:16:08 by ferid             #+#    #+#             */
/*   Updated: 2025/01/21 17:16:11 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../cub3d.h"

void
    start_weapon_animation(
        t_scene *scene)
{
    if (!scene->weapon.is_animating) {
        scene->weapon.is_animating = true;
        scene->weapon.current_frame = 0;
        scene->weapon.texture = scene->weapon.textures[0];
        scene->recast = true;
    }
}

void
    next_weapon_frame(
        t_scene *scene)
{
    if (!scene->weapon.is_animating)
        return;
    scene->weapon.current_frame++;
    if (scene->weapon.current_frame >= 6) {
        scene->weapon.current_frame = 0;
        scene->weapon.is_animating = false;
    }
    scene->weapon.texture = scene->weapon.textures[scene->weapon.current_frame];
    scene->recast = true;
} 