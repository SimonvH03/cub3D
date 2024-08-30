/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 02:16:08 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "defs.h"

//// PHASE 0: initialising mlx window, scene and camera
short		init(t_window *window, char *argv_scene);
short		map_read(t_scene *scene);
void		camera_init(t_camera *camera, int x, int y, char direction);
short		init_images(t_window *window);
void		draw_scene_background(t_scene *scene);
void		draw_minimap_border_overlay(t_minimap *minimap);

//// PHASE 1: interpreting user input to change camera data
mlx_hook	user_inputs;
mlx_key		keyhook;
mlx_scroll	scrollhook;
void		wasd_move(t_window *window);
void		rotate_camera(t_camera *camera);

//// PHASE 2: drawing the raycast
mlx_hook	draw_minimap;
mlx_hook	draw_raycast;
//// UTILS
// scene
int			scene_free(t_scene *scene);
// draw
void		reset_image(mlx_image_t *image);
uint32_t	gradient(float ratio, uint32_t end, uint32_t start);
// calc
short		is_in_circle(float a, float b, float r, float x, float y);
float		deg_to_rad(float angle_deg);
float		ft_max_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);
// test
void		print_camera(t_camera *camera);
void		print_map(t_scene *scene);
void		print_ray(t_ray *ray);

#endif