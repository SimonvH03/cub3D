#include "../defs.h"

void game_loop(void *param)
{
    t_window *window = param;
    
    if (window->view == GAME) {
        // Update door animations
        update_doors(&window->scene);
        
        // Your existing game loop code
        // ...
    }
}

void init_game(t_window *window)
{
    // Your existing initialization code
    // ...
    
    // Initialize door system
    init_door_manager(&window->scene);
}

void cleanup_game(t_window *window)
{
    // Your existing cleanup code
    // ...
    
    // Cleanup door system
    cleanup_door_manager(&window->scene);
} 