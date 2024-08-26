/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	cub3d_scale_init(
		t_cub3d *cub3d)
{
	double	scalefinder;

	cub3d->scale.initial = (double)cub3d->image->width / (double)cub3d->map->x_max;
	scalefinder = (double)cub3d->image->height / (double)cub3d->map->y_max;
	if (scalefinder < cub3d->scale.initial)
		cub3d->scale.initial = scalefinder;
	if (cub3d->map->radius == 0)
		cub3d->scale.sphere = 1;
	else
		cub3d->scale.sphere = cub3d->image->width / (2.2 * cub3d->map->radius)
			* DEFAULT_SCALE;
	cub3d->scale.initial *= DEFAULT_SCALE;
	if (cub3d->scale.initial == 0)
		cub3d->scale.initial = 0.1;
	cub3d->scale.diff = cub3d->scale.initial;
	cub3d->scale.total = 1;
}

static int
	cub3d_mlx_init(
		t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (cub3d->mlx == NULL)
		return (EXIT_FAILURE);
	cub3d->image = mlx_new_image(cub3d->mlx, WIDTH - MENU_WIDTH, HEIGHT);
	if (cub3d->image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(cub3d->mlx, cub3d->image, MENU_WIDTH, 0) < 0)
		return (EXIT_FAILURE);
	cub3d->menu_image = mlx_new_image(cub3d->mlx, MENU_WIDTH, HEIGHT);
	if (cub3d->menu_image == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// from main.c / main()
int
	cub3d_init(
		t_cub3d *cub3d,
		t_map *map)
{
	if (cub3d_mlx_init(cub3d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cub3d->map = map;
	cub3d->perspective = (t_perspective){ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
	cub3d->precalc = (t_precalc){0, 0, 0, 1, true};
	cub3d->speed = ROTATION_SPEED;
	cub3d->cosin = (t_cosin){cos(cub3d->speed), sin(cub3d->speed)};
	cub3d_scale_init(cub3d);
	cub3d->radius = cub3d->map->radius;
	cub3d->darksquare = cub3d->radius / sqrt(2);
	cub3d_center_offset(cub3d);
	cub3d->spinlock = false;
	cub3d->redraw = true;
	cub3d->ballin = false;
	cub3d->horizon = true;
	return (EXIT_SUCCESS);
}
