/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/09/17 03:28:56 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "defs.h"
# include "paths.h"

void		error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message);
void		cub3d_terminate(t_window *window);

//// PHASE 0: initialising mlx window, scene and camera
short		window_init(t_window *window);

short		init_game_structs(mlx_t *mlx, t_window *window, char *argv_scene);
short		get_content(t_scene *scene);
void		read_elements(t_scene *scene);
short		read_map(t_scene *scene);

short		init_game_images(mlx_t *mlx, t_window *window);
void		draw_scene_background(t_scene *scene);
void		draw_minimap_circle_overlay(t_minimap *minimap);
void		draw_map_walls(t_map *map);

short		init_menu_structs(mlx_t *mlx, t_menu *menu);
short		init_menu_images(mlx_t *mlx, t_menu *menu);
void		draw_scaled_image(t_scalable *scalable);
// void		draw_menu_highlight(mlx_image_t *image);

// interpretation of user inputs
mlx_key		window_keyhook;
mlx_hook	view_manager;
void		wasd_move(t_window *window, t_camera *camera);
void		arrowkey_turn(t_window *window, t_camera *camera);
void		up_down_select(t_menu *menu);
void		confirm_selection(t_menu *menu, t_window *window);
void		toggle_maps(t_minimap *minimap, t_map *map);
void		toggle_view(t_window *window);

// Door system functions
void init_door_manager(t_scene *scene);
void cleanup_door_manager(t_scene *scene);
bool is_door(int tile);
bool is_solid(int tile);
t_door_state *get_door_at_position(t_scene *scene, int x, int y);
void interact_with_door(t_scene *scene, t_camera *camera);
void update_door_animations(t_scene *scene, float delta_time);

// frame processing
void		draw_raycast(t_scene *scene);
void		draw_texture_column(t_scene *scene, t_ray *ray, uint32_t x);
void		init_column(t_scene *scene, t_ray *ray, t_column *column);
void		draw_minimap_walls(t_minimap *minimap);
void		draw_map_player(t_map *map);

// ray casting functions
void        init_ray(t_ray *ray, t_camera *camera);
void        update_ray_position(t_ray *ray);
void        update_final_ray_position(t_ray *ray);
bool        check_wall_hit(t_ray *ray, t_scene *scene);
void        check_door_hit(t_ray *ray, t_scene *scene);
void        cast_ray(t_ray *ray, t_scene *scene);

// arithmetic
float		ft_max_float(float a, float b);
float		ft_min_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);
// modlx
void		reset_image(mlx_image_t *image);

// TEST
// void		print_camera(t_camera *camera);
// void		print_ray(t_ray *ray);
// void		print_minimap(t_minimap *minimap);
// void		print_content(t_scene *scene);
// void		print_map(t_scene *scene);
// void		draw_textures(t_window *window);

#endif