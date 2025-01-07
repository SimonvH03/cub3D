/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Initialize the HUD elements
*/
short
    init_hud(
        mlx_t *mlx,
        t_hud *hud)
{
    printf("Initializing HUD...\n");
    
    // Store MLX instance
    hud->mlx = mlx;

    // Initialize health bar background
    hud->health_bar_bg = mlx_new_image(mlx, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT);
    if (!hud->health_bar_bg)
    {
        printf("Failed to create health bar background image\n");
        return (EXIT_FAILURE);
    }
    
    // Fill health bar background with color
    uint32_t *pixels = (uint32_t *)hud->health_bar_bg->pixels;
    for (uint32_t i = 0; i < HEALTH_BAR_WIDTH * HEALTH_BAR_HEIGHT; i++)
        pixels[i] = C_HEALTH_BAR_BG;
    
    // Add to window with high Z-index
    if (mlx_image_to_window(mlx, hud->health_bar_bg, 20, HEIGHT - HEALTH_BAR_HEIGHT - 20) < 0)
    {
        printf("Failed to add health bar background to window\n");
        return (EXIT_FAILURE);
    }
    hud->health_bar_bg->instances[0].z = 10;

    // Initialize health bar
    hud->health_bar = mlx_new_image(mlx, HEALTH_BAR_WIDTH - 4, HEALTH_BAR_HEIGHT - 4);
    if (!hud->health_bar)
    {
        printf("Failed to create health bar image\n");
        return (EXIT_FAILURE);
    }
    
    // Fill health bar with color
    pixels = (uint32_t *)hud->health_bar->pixels;
    for (uint32_t i = 0; i < (HEALTH_BAR_WIDTH - 4) * (HEALTH_BAR_HEIGHT - 4); i++)
        pixels[i] = C_HEALTH_BAR;
    
    // Add to window with high Z-index
    if (mlx_image_to_window(mlx, hud->health_bar, 22, HEIGHT - HEALTH_BAR_HEIGHT - 18) < 0)
    {
        printf("Failed to add health bar to window\n");
        return (EXIT_FAILURE);
    }
    hud->health_bar->instances[0].z = 11;

    // Initialize crosshair
    hud->crosshair = mlx_new_image(mlx, CROSSHAIR_SIZE * 2 + 1, CROSSHAIR_SIZE * 2 + 1);
    if (!hud->crosshair)
    {
        printf("Failed to create crosshair image\n");
        return (EXIT_FAILURE);
    }
    
    // Draw crosshair (thicker lines)
    for (int i = 0; i < CROSSHAIR_SIZE * 2 + 1; i++)
    {
        // Vertical line
        mlx_put_pixel(hud->crosshair, CROSSHAIR_SIZE - 1, i, C_CROSSHAIR);
        mlx_put_pixel(hud->crosshair, CROSSHAIR_SIZE, i, C_CROSSHAIR);
        mlx_put_pixel(hud->crosshair, CROSSHAIR_SIZE + 1, i, C_CROSSHAIR);
        
        // Horizontal line
        mlx_put_pixel(hud->crosshair, i, CROSSHAIR_SIZE - 1, C_CROSSHAIR);
        mlx_put_pixel(hud->crosshair, i, CROSSHAIR_SIZE, C_CROSSHAIR);
        mlx_put_pixel(hud->crosshair, i, CROSSHAIR_SIZE + 1, C_CROSSHAIR);
    }
    
    // Add to window with highest Z-index
    if (mlx_image_to_window(mlx, hud->crosshair, WIDTH / 2 - CROSSHAIR_SIZE, HEIGHT / 2 - CROSSHAIR_SIZE) < 0)
    {
        printf("Failed to add crosshair to window\n");
        return (EXIT_FAILURE);
    }
    hud->crosshair->instances[0].z = 12;

    // Initialize interaction prompt
    hud->prompt = mlx_new_image(mlx, WIDTH, PROMPT_HEIGHT);
    if (!hud->prompt)
    {
        printf("Failed to create prompt image\n");
        return (EXIT_FAILURE);
    }
    
    // Add to window with high Z-index
    if (mlx_image_to_window(mlx, hud->prompt, 0, HEIGHT - PROMPT_HEIGHT - 100) < 0)
    {
        printf("Failed to add prompt to window\n");
        return (EXIT_FAILURE);
    }
    hud->prompt->instances[0].z = 11;

    // Set initial values
    hud->max_health = 100;
    hud->current_health = 100;
    hud->show_prompt = true; // Set to true initially for testing
    hud->prompt_text = "Press E to interact"; // Set test text

    // Draw initial prompt
    if (hud->show_prompt)
    {
        // Draw a test line for the prompt
        for (uint32_t x = WIDTH/2 - 100; x < WIDTH/2 + 100; x++)
        {
            for (uint32_t y = 0; y < PROMPT_HEIGHT; y++)
            {
                mlx_put_pixel(hud->prompt, x, y, C_PROMPT_TEXT);
            }
        }
    }

    printf("HUD initialization complete\n");
    return (EXIT_SUCCESS);
}

/*
** Update HUD elements based on game state
*/
void
    update_hud(
        t_hud *hud,
        t_scene *scene)
{
    // Update health bar width based on current health
    float health_ratio = (float)hud->current_health / hud->max_health;
    int health_width = (int)((HEALTH_BAR_WIDTH - 4) * health_ratio);
    
    // Clear health bar
    ft_memset(hud->health_bar->pixels, 0, (HEALTH_BAR_WIDTH - 4) * (HEALTH_BAR_HEIGHT - 4) * sizeof(int));
    
    // Draw new health bar
    int y = 0;
    while (y < HEALTH_BAR_HEIGHT - 4)
    {
        int x = 0;
        while (x < health_width)
        {
            mlx_put_pixel(hud->health_bar, x, y, C_HEALTH_BAR);
            x++;
        }
        y++;
    }

    // Update interaction prompt
    if (hud->show_prompt)
    {
        // Clear prompt
        ft_memset(hud->prompt->pixels, 0, WIDTH * PROMPT_HEIGHT * sizeof(int));
        
        // Draw prompt text if needed
        if (hud->prompt_text)
        {
            // Text rendering would go here
            // For now, we'll just show a simple indicator
            int x = WIDTH / 2 - 50;
            while (x < WIDTH / 2 + 50)
            {
                mlx_put_pixel(hud->prompt, x, PROMPT_HEIGHT / 2, C_PROMPT_TEXT);
                x++;
            }
        }
    }
    
    // Ensure scene is marked for update if needed
    (void)scene;
} 