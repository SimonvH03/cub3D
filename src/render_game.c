/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../defs.h"

// Get the door texture color based on animation progress
int get_door_texture_color(t_scene *scene, int x, int y, float tex_x, float tex_y)
{
    t_door_state *door = get_door_at_position(scene, x, y);
    if (!door)
        return 0xff000000;

    // Get the base texture coordinate
    float adjusted_x = get_door_texture_x(door, tex_x);
    
    // Get color from door texture
    if (adjusted_x >= 0 && adjusted_x < 64) // Assuming texture width is 64
    {
        return *(int *)(scene->door_texture.addr + 
            ((int)tex_y * scene->door_texture.line_len + 
             (int)adjusted_x * (scene->door_texture.bpp / 8)));
    }
    
    return 0xff000000;
}

void render_game()
{
    if (cnt == 10)
    {
        cnt = 0;
        if (data.objects.health > 0)
        {
            // ... existing movement code ...

            // Update door states
            update_doors(&data.scene);

            // Update door animation progress
            for (int i = 0; i < data.scene.door_manager.door_count; i++)
            {
                t_door_state *door = &data.scene.door_manager.doors[i];
                
                if (door->is_opening)
                {
                    door->animation_progress += door->animation_speed * 0.016f; // Assuming 60 FPS
                    if (door->animation_progress >= 1.0f)
                    {
                        door->animation_progress = 1.0f;
                        door->is_opening = false;
                        data.scene.map[door->y][door->x] = TILE_DOOR_OPEN;
                    }
                    data.scene.recast = true;
                }
                else if (door->is_closing)
                {
                    door->animation_progress -= door->animation_speed * 0.016f;
                    if (door->animation_progress <= 0.0f)
                    {
                        door->animation_progress = 0.0f;
                        door->is_closing = false;
                        data.scene.map[door->y][door->x] = TILE_DOOR;
                    }
                    data.scene.recast = true;
                }
            }
        }

        // ... rest of the game update code ...
    }
    cnt++;
}

// ... rest of the file unchanged ... 