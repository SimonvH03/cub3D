/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/14 01:28:57 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	new_images_scene(
		t_window *window,
		t_scene *scene)
{
	xpm_t	*tempx;

	tempx = mlx_load_xpm42(PLAYER_ICON_PATH);
	if (tempx == NULL)
		return (EXIT_FAILURE);
	scene->player_texture = &tempx->texture;
	scene->background = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (scene->background == NULL)
		return (EXIT_FAILURE);
	scene->walls = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (scene->walls == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, scene->background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, scene->walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static short
	new_images_minimap(
		t_window *window,
		t_minimap *minimap)
{
	xpm_t	*tempx;

	minimap->walls = mlx_new_image(window->mlx,
			minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (EXIT_FAILURE);
	minimap->player = mlx_texture_to_image(window->mlx,
			window->scene.player_texture);
	if (minimap->player == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, minimap->walls,
			window->mlx->width - minimap->side * 1.2,
			window->mlx->height - minimap->side * 1.2) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, minimap->player,
			minimap->walls->instances[0].x + minimap->radius
			- minimap->player->width / 2,
			minimap->walls->instances[0].y + minimap->radius
			- minimap->player->height / 2) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static short
	new_images_map(
		t_window *window,
		t_map *map)
{
	map->walls = mlx_new_image(window->mlx,
			window->mlx->width,
			window->mlx->height);
	if (map->walls == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, map->walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	map->player = mlx_new_image(window->mlx,
			window->scene.player_texture->width * sqrt(2),
			window->scene.player_texture->height * sqrt(2));
	if (map->player == NULL)
		return (EXIT_FAILURE);
	map->x_offset = window->mlx->width - map->scene->x_max / map->scale;
	map->y_offset = window->mlx->height - map->scene->y_max / map->scale;
	map->x_offset -= map->player->width;
	map->y_offset -= map->player->height;
	map->x_offset /= 2;
	map->y_offset /= 2;
	if (mlx_image_to_window(window->mlx, map->player,
			map->x_offset + map->scene->camera.pos_x / map->scale,
			map->y_offset + map->scene->camera.pos_y / map->scale) < 0)
		return (EXIT_FAILURE);
	map->player->enabled = false;
	map->walls->enabled = false;
	return (EXIT_SUCCESS);
}

static short
	new_images_menu(
		t_window *window,
		t_menu *menu)
{
	xpm_t			*tempx;
	mlx_texture_t	*temp;
	uint32_t		button_x_offset;
	uint32_t		button_y_offset;

	temp = mlx_load_png(MENU_BACKGROUND_PATH);
	if (temp == NULL)
		return (EXIT_FAILURE);
	menu->background = mlx_texture_to_image(window->mlx, temp);
	if (menu->background == NULL)
		return (EXIT_FAILURE);
	tempx = mlx_load_xpm42(MENU_BUTTON_START_PATH);
	if (tempx == NULL)
		return (EXIT_FAILURE);
	menu->button_start = mlx_texture_to_image(window->mlx, &tempx->texture);
	if (menu->button_start == NULL)
		return (EXIT_FAILURE);
	tempx = mlx_load_xpm42(MENU_BUTTON_QUIT_PATH);
	if (tempx == NULL)
		return (EXIT_FAILURE);
	menu->button_quit = mlx_texture_to_image(window->mlx, &tempx->texture);
	if (menu->button_quit == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, menu->background, 0, 0) < 0)
		return (EXIT_FAILURE);
	button_x_offset = window->mlx->width / 2 - menu->button_start->width / 2;
	button_y_offset = window->mlx->height / 2 - menu->button_start->height * 2;
	if (mlx_image_to_window(window->mlx, menu->button_start,
			button_x_offset, button_y_offset) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, menu->button_quit, button_x_offset,
			button_y_offset + menu->button_start->height * 3) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

short
	init_images(
		t_window *window)
{
	if (new_images_scene(window, &window->scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_minimap(window, &window->minimap) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_map(window, &window->map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_menu(window, &window->menu) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_scene_background(&window->scene);
	draw_minimap_circle_overlay(&window->minimap);
	draw_map_walls(&window->map);
	// init_hud();
	window->fps = mlx_put_string(window->mlx, "000", WIDTH / 2 - 50, 100);
	return (EXIT_SUCCESS);
}
