#include "../defs.h"

#define DOOR_ANIMATION_SPEED 2.0f
#define DOOR_INTERACTION_RANGE 1.5f
#define DOOR_ANIMATION_STEP 0.016f

void init_door_manager(t_scene *scene)
{
    int x, y;
    int count = 0;
    int sprite_index = 0;

    // First count the number of doors
    for (y = 0; y < scene->y_max; y++) {
        for (x = 0; x < scene->x_max; x++) {
            if (scene->map[y][x] == TILE_DOOR)
                count++;
        }
    }

    // Initialize door manager
    scene->door_manager.doors = malloc(sizeof(t_door_state) * count);
    scene->door_manager.door_count = count;
    scene->door_manager.interaction_range = DOOR_INTERACTION_RANGE;

    // Initialize each door and its corresponding sprite
    count = 0;
    for (y = 0; y < scene->y_max; y++) {
        for (x = 0; x < scene->x_max; x++) {
            if (scene->map[y][x] == TILE_DOOR) {
                // Initialize door state
                scene->door_manager.doors[count].is_opening = false;
                scene->door_manager.doors[count].is_closing = false;
                scene->door_manager.doors[count].animation_progress = 0.0f;
                scene->door_manager.doors[count].animation_speed = DOOR_ANIMATION_SPEED;
                scene->door_manager.doors[count].x = x;
                scene->door_manager.doors[count].y = y;

                // Initialize corresponding sprite if we have room
                if (sprite_index < scene->active_sprites) {
                    scene->sprites[sprite_index].x = x;
                    scene->sprites[sprite_index].y = y;
                    scene->sprites[sprite_index].state = ANIM_IDLE;
                    scene->sprites[sprite_index].current_frame = FRAME_DOOR_CLOSED;
                    scene->sprites[sprite_index].anim_timer = 0.0f;
                    scene->sprites[sprite_index].recast = true;
                    sprite_index++;
                }
                count++;
            }
        }
    }
}

void update_doors(t_scene *scene)
{
    float dx, dy, distance;
    t_door_state *door;
    t_sprite_data *sprite;
    int i;

    for (i = 0; i < scene->door_manager.door_count; i++) {
        door = &scene->door_manager.doors[i];
        sprite = NULL;

        // Find corresponding sprite
        for (int j = 0; j < scene->active_sprites; j++) {
            if ((int)scene->sprites[j].x == door->x && 
                (int)scene->sprites[j].y == door->y) {
                sprite = &scene->sprites[j];
                break;
            }
        }

        // Calculate distance to player
        dx = scene->camera.pos_x - door->x;
        dy = scene->camera.pos_y - door->y;
        distance = sqrtf(dx * dx + dy * dy);

        // Handle door state based on player distance and interaction
        if (distance <= scene->door_manager.interaction_range && 
            scene->input.interact_pressed) {
            if (!door->is_opening && door->animation_progress < 1.0f) {
                door->is_opening = true;
                door->is_closing = false;
                if (sprite) {
                    sprite->state = ANIM_OPENING;
                    sprite->anim_timer = 0.0f;
                }
            }
            else if (!door->is_closing && door->animation_progress > 0.0f) {
                door->is_closing = true;
                door->is_opening = false;
                if (sprite) {
                    sprite->state = ANIM_CLOSING;
                    sprite->anim_timer = 0.0f;
                }
            }
        }

        // Update animation progress
        if (door->is_opening) {
            door->animation_progress += door->animation_speed * DOOR_ANIMATION_STEP;
            if (door->animation_progress >= 1.0f) {
                door->animation_progress = 1.0f;
                door->is_opening = false;
                scene->map[door->y][door->x] = TILE_DOOR_OPEN;
            }
        } else if (door->is_closing) {
            door->animation_progress -= door->animation_speed * DOOR_ANIMATION_STEP;
            if (door->animation_progress <= 0.0f) {
                door->animation_progress = 0.0f;
                door->is_closing = false;
                scene->map[door->y][door->x] = TILE_DOOR;
            }
        }
    }
    scene->recast = true;
}

void cleanup_door_manager(t_scene *scene)
{
    if (scene->door_manager.doors) {
        free(scene->door_manager.doors);
        scene->door_manager.doors = NULL;
    }
    scene->door_manager.door_count = 0;
}

// Get the door state at a specific position
t_door_state *get_door_at_position(t_scene *scene, int x, int y)
{
    int i;
    for (i = 0; i < scene->door_manager.door_count; i++) {
        if (scene->door_manager.doors[i].x == x && 
            scene->door_manager.doors[i].y == y) {
            return &scene->door_manager.doors[i];
        }
    }
    return NULL;
} 