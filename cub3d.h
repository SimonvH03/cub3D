/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/09/08 18:40:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "defs.h"

void		error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message);

//// PHASE 0: initialising mlx window, scene and camera
short		init_structs(t_window *window, char *argv_scene);
short		init_images(t_window *window);
short		get_content(t_scene *scene);
void		read_elements(t_scene *scene);
short		read_map(t_scene *scene);
void		camera_init(t_camera *camera, int pos_x, int pos_y, char cardinal);
short		init_images(t_window *window);
void		draw_scene_background(t_scene *scene);
void		draw_minimap_circle_overlay(t_minimap *minimap);
void		draw_map_walls(t_map *map);

//// PHASE 1: interpreting user input to change menu, game and camera view
mlx_key		keyhook;
mlx_scroll	scrollhook;
void		game_inputs(t_window *window);
void		menu_inputs(t_window *window);

void		wasd_move(t_window *window);
void		arrowkey_turn(t_window *window);
void		toggle_maps(t_minimap *minimap, t_map *map);

//// PHASE 2: drawing the current view
void		draw_raycast(t_scene *scene);
void		draw_minimap(t_minimap *minimap);
void		draw_map_player(t_map *map);

//// UTILS
// scene
int			scene_free(t_scene *scene);
// draw
void		reset_image(mlx_image_t *image);
uint32_t	gradient(double ratio, uint32_t end, uint32_t start);
// calc
short		is_in_circle(double x_minus_a, double y_minus_b, double radius);
// short		is_in_circle(double a, double b, double r, double x, double y);
double		deg_to_rad(double angle_deg);
double		ft_max_double(double a, double b);
double		ft_abs_double(double value);
short		ft_sign_double(double value);
// test
void		print_camera(t_camera *camera);
void		print_content(t_scene *scene);
void		print_map(t_scene *scene);
void		print_ray(t_ray *ray);
void		draw_textures(t_window *window);

#endif