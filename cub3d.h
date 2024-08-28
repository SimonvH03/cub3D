/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/08/28 22:11:41 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "defs.h"

//// PHASE 1: initialising mlx window, scene and camera
short		init(t_window *window, char *argv_scene);
short		scene_init(t_scene *scene, char *argv_scene);
short		map_read(t_scene *scene);
void		camera_init(t_camera *camera, int x, int y, char direction);
short		init_images(t_window *window);
// void		hud_draw(t_window *window);

//// PHASE 2: interpreting user input to change camera data
mlx_hook	user_inputs;
mlx_key		keyhook;
mlx_scroll	scrollhook;
void		rotate_camera(t_camera *camera);

//// PHASE 4: drawing the raycast
mlx_hook	raycast;
//// UTILS
// scene
int			scene_free(t_scene *scene);
// draw
void		reset_image(mlx_image_t *image);
void		draw_background(t_scene *scene, mlx_image_t *image);
uint32_t	gradient(float ratio, uint32_t end, uint32_t start);
// calc
float		deg_to_rad(float angle_deg);
float		ft_max_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);
// test
void		print_camera(t_camera *camera);
void		print_map(t_scene *scene);
void		print_ray(t_ray *ray);

#endif