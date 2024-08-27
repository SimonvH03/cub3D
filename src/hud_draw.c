/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 23:10:28 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	menu_print_2(
		t_cub3d *cub3d,
		int x,
		int y)
{
	const int	margin = 48;
	const int	line = 24;
	const int	tab = 144;

	mlx_put_string(cub3d->mlx, "ROTATION", x, y += margin);
	mlx_put_string(cub3d->mlx, "Pitch:", x, y += line);
	mlx_put_string(cub3d->mlx, "W - S", x + tab, y);
	mlx_put_string(cub3d->mlx, "Yaw:", x, y += line);
	mlx_put_string(cub3d->mlx, "A - D", x + tab, y);
	mlx_put_string(cub3d->mlx, "Roll:", x, y += line);
	mlx_put_string(cub3d->mlx, "Q - E", x + tab, y);
	mlx_put_string(cub3d->mlx, "Zoom:", x, y += margin);
	mlx_put_string(cub3d->mlx, "Scroll UP - DOWN", x + tab, y);
	mlx_put_string(cub3d->mlx, "Spinlock:", x, y += line);
	mlx_put_string(cub3d->mlx, "SPACEBAR", x + tab, y);
	mlx_put_string(cub3d->mlx, "Horizon:", x, y += line);
	mlx_put_string(cub3d->mlx, "H", x + tab, y);
	mlx_put_string(cub3d->mlx, "Colour cycle:", x, y += line);
	mlx_put_string(cub3d->mlx, "C", x + tab, y);
	mlx_put_string(cub3d->mlx, "Reset:", x, y += line);
	mlx_put_string(cub3d->mlx, "R", x + tab, y);
}

static void
	menu_print_1(
		t_cub3d *cub3d)
{
	const int	margin = 48;
	const int	line = 24;
	const int	tab = 144;
	int			x;
	int			y;

	mlx_put_string(cub3d->mlx, cub3d->scene->name, x = margin, y = margin);
	mlx_put_string(cub3d->mlx, "PRESETS", x, y += margin);
	mlx_put_string(cub3d->mlx, "Parallel", x, y += line);
	mlx_put_string(cub3d->mlx, "P", x + tab, y);
	mlx_put_string(cub3d->mlx, "Isometric", x, y += line);
	mlx_put_string(cub3d->mlx, "I", x + tab, y);
	mlx_put_string(cub3d->mlx, "Globe", x, y += line);
	mlx_put_string(cub3d->mlx, "O", x + tab, y);
	mlx_put_string(cub3d->mlx, "Radar", x, y += line);
	mlx_put_string(cub3d->mlx, "U", x + tab, y);
	mlx_put_string(cub3d->mlx, "TRANSLATION", x, y += margin);
	mlx_put_string(cub3d->mlx, "Move:", x, y += line);
	mlx_put_string(cub3d->mlx, "Arrow Keys", x + tab, y);
	mlx_put_string(cub3d->mlx, "Switch Mode:", x, y += line);
	mlx_put_string(cub3d->mlx, "T", x + tab, y);
	menu_print_2(cub3d, x, y);
}

// from main.c main()
void
	hud_draw(
		t_cub3d *cub3d)
{
	// draw_background(cub3d->menu_image, C_MENU);
	// mlx_image_to_window(cub3d->mlx, cub3d->menu_image, 0, 0);
	menu_print_1(cub3d);
}
