/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/09/16 16:43:27 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "defs.h"
# include "paths.h"
# include "modlx_font.h"

void		error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message);
void		cub3d_terminate(t_window *window);

//// PHASE 0: initialising mlx window, scene and camera
short		init_game_structs(t_window *window, char *argv_scene);
short		get_content(t_scene *scene);
void		read_elements(t_scene *scene);
short		read_map(t_scene *scene);

short		init_game_images(t_window *window);
void		draw_scene_background(t_scene *scene);
void		draw_minimap_circle_overlay(t_minimap *minimap);
void		draw_map_walls(t_map *map);

short		init_menu_structs(t_window *window);
short		init_menu_images(t_window *window);
void		draw_scaled_image(t_scalable *scalable);

// interpretation of user inputs
void		game_inputs(t_window *window);
void		wasd_move(t_window *window, t_camera *camera);
void		arrowkey_turn(t_window *window, t_camera *camera);

void		menu_inputs(t_window *window);
//

mlx_key		keyhook;
mlx_hook	view_manager;
void		toggle_maps(t_minimap *minimap, t_map *map);
void		toggle_view(t_window *window);

// frame processing
void		draw_raycast(t_scene *scene);
void		draw_texture_column(t_scene *scene, t_ray *ray, uint32_t x);
void		draw_minimap_walls(t_minimap *minimap);
void		draw_map_player(t_map *map);
// arithmetic
float		ft_max_float(float a, float b);
float		ft_min_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);
// modlx
void		modlx_reset_image(mlx_image_t *image);
void		modlx_replace_string(mlx_image_t* strimage, const char* str);

// TEST
// void		print_camera(t_camera *camera);
// void		print_ray(t_ray *ray);
// void		print_minimap(t_minimap *minimap);
// void		print_content(t_scene *scene);
// void		print_map(t_scene *scene);
// void		draw_textures(t_window *window);

#endif