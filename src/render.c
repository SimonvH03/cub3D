#include "../defs.h"

// Add this function to handle door texture rendering
mlx_texture_t *get_door_texture(t_scene *scene, t_ray *ray, float *tex_x)
{
    t_door_state *door = get_door_at_position(scene, ray->pos_x, ray->pos_y);
    if (!door)
        return scene->door_texture;

    // Adjust texture X coordinate based on animation progress
    if (ray->hit_type == HORIZONTAL) {
        *tex_x = ray->total_x - floor(ray->total_x);
        // Slide door horizontally
        *tex_x = *tex_x + door->animation_progress;
        if (*tex_x > 1.0f)
            *tex_x = 1.0f;
    } else {
        *tex_x = ray->total_y - floor(ray->total_y);
        // Slide door vertically
        *tex_x = *tex_x + door->animation_progress;
        if (*tex_x > 1.0f)
            *tex_x = 1.0f;
    }

    return scene->door_texture;
}

// Modify your existing render_column function to handle doors
void render_column(t_scene *scene, t_ray *ray, int x)
{
    t_column column;
    float tex_x;

    column.height = (int)(HEIGHT / ray->distance);
    column.start = -column.height / 2 + HEIGHT / 2;
    column.end = column.height / 2 + HEIGHT / 2;

    if (scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR ||
        scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR_OPEN) {
        column.texture = get_door_texture(scene, ray, &tex_x);
    } else {
        // Your existing texture selection code for walls
        if (ray->hit_type == HORIZONTAL) {
            tex_x = ray->total_x - floor(ray->total_x);
            column.texture = (ray->sign_y > 0) ? scene->north_texture : scene->south_texture;
        } else {
            tex_x = ray->total_y - floor(ray->total_y);
            column.texture = (ray->sign_x > 0) ? scene->west_texture : scene->east_texture;
        }
    }

    // Draw the column
    column.x = tex_x * column.texture->width;
    column.step = column.texture->height / (float)column.height;
    column.y = 0;

    // Clamp drawing bounds
    if (column.start < 0) {
        column.y = -column.start * column.step;
        column.start = 0;
    }
    if (column.end >= HEIGHT)
        column.end = HEIGHT - 1;

    // Draw the column
    while (column.start < column.end) {
        uint8_t *pixel = &scene->walls->pixels[(column.start * scene->walls->width + x) * BPP];
        uint8_t *tex = &column.texture->pixels[((int)column.y % column.texture->height) * column.texture->width * BPP + (int)column.x * BPP];
        
        // Only draw if the texture pixel is not transparent
        if (tex[3] != 0) {
            pixel[0] = tex[0];
            pixel[1] = tex[1];
            pixel[2] = tex[2];
            pixel[3] = tex[3];
        }
        
        column.y += column.step;
        column.start++;
    }
} 