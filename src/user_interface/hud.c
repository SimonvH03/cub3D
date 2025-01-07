/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/18 17:51:08 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
    draw_health_bar(
        t_hud *hud)
{
    int fill_width;
    int x;
    int y;

    // Clear previous health bar
    for (y = 0; y < HEALTH_BAR_HEIGHT; y++)
    {
        for (x = 0; x < HEALTH_BAR_WIDTH; x++)
        {
            mlx_put_pixel(hud->health_bar_bg, x, y, C_HEALTH_BAR_BG);
            mlx_put_pixel(hud->health_bar, x, y, 0x00000000);  // Clear with transparent
        }
    }

    // Draw health bar fill based on current health
    fill_width = (hud->current_health * HEALTH_BAR_WIDTH) / hud->max_health;
    for (y = 0; y < HEALTH_BAR_HEIGHT; y++)
    {
        for (x = 0; x < fill_width; x++)
        {
            mlx_put_pixel(hud->health_bar, x, y, C_HEALTH_BAR);
        }
    }
}

static void
    draw_crosshair(
        t_hud *hud)
{
    int center_x = CROSSHAIR_SIZE;
    int center_y = CROSSHAIR_SIZE;
    int x, y;

    // Clear previous crosshair
    for (y = 0; y < CROSSHAIR_SIZE * 2 + 1; y++)
    {
        for (x = 0; x < CROSSHAIR_SIZE * 2 + 1; x++)
        {
            mlx_put_pixel(hud->crosshair, x, y, 0x00000000);  // Clear with transparent
        }
    }

    // Draw horizontal line
    for (x = 0; x < CROSSHAIR_SIZE * 2 + 1; x++)
    {
        mlx_put_pixel(hud->crosshair, x, center_y, C_CROSSHAIR);
    }

    // Draw vertical line
    for (y = 0; y < CROSSHAIR_SIZE * 2 + 1; y++)
    {
        mlx_put_pixel(hud->crosshair, center_x, y, C_CROSSHAIR);
    }
}

static void
    draw_prompt(
        t_hud *hud)
{
    // Clear previous prompt
    for (int y = 0; y < PROMPT_HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            mlx_put_pixel(hud->prompt, x, y, 0x00000000);  // Clear with transparent
        }
    }

    // Draw new prompt if needed
    if (hud->show_prompt && hud->prompt_text)
    {
        mlx_put_string(hud->mlx, hud->prompt_text, WIDTH / 2 - 50, PROMPT_HEIGHT / 2);
    }
}

void
    init_hud(
        mlx_t *mlx,
        t_hud *hud)
{
    // Initialize HUD state
    hud->max_health = 100;
    hud->current_health = 100;
    hud->show_prompt = false;
    hud->prompt_text = NULL;
    hud->mlx = mlx;

    // Create HUD images
    hud->health_bar_bg = mlx_new_image(mlx, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT);
    hud->health_bar = mlx_new_image(mlx, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT);
    hud->crosshair = mlx_new_image(mlx, CROSSHAIR_SIZE * 2 + 1, CROSSHAIR_SIZE * 2 + 1);
    hud->prompt = mlx_new_image(mlx, WIDTH, PROMPT_HEIGHT);

    // Position HUD elements
    mlx_image_to_window(mlx, hud->health_bar_bg, 20, HEIGHT - HEALTH_BAR_HEIGHT - 20);
    mlx_image_to_window(mlx, hud->health_bar, 20, HEIGHT - HEALTH_BAR_HEIGHT - 20);
    mlx_image_to_window(mlx, hud->crosshair, 
        WIDTH / 2 - CROSSHAIR_SIZE, 
        HEIGHT / 2 - CROSSHAIR_SIZE);
    mlx_image_to_window(mlx, hud->prompt, 0, HEIGHT - PROMPT_HEIGHT - 60);

    // Initial draw
    draw_health_bar(hud);
    draw_crosshair(hud);
}

void
    update_hud(
        t_hud *hud,
        t_scene *scene)
{
    // Update health bar if health changed
    draw_health_bar(hud);

    // Update crosshair (static, but could be dynamic based on weapon state)
    draw_crosshair(hud);

    // Check for interactive objects and update prompt
    int check_x = (int)(scene->camera.pos_x + scene->camera.dir_x * 0.5);
    int check_y = (int)(scene->camera.pos_y + scene->camera.dir_y * 0.5);

    if (is_door(scene->map[check_y][check_x]))
    {
        hud->show_prompt = true;
        hud->prompt_text = "Press E to interact";
    }
    else
    {
        hud->show_prompt = false;
        hud->prompt_text = NULL;
    }
    draw_prompt(hud);
} 