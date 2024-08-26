/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graveyard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:00:58 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// victim #1: replaced by map_iteration version
// void
// 	cub3d_draw(
// 		void *param)
// {
// 	t_cub3d	*cub3d;
// 	int		y;
// 	int		x;

// 	cub3d = param;
// 	if (cub3d->redraw == false)
// 		return ;
// 	draw_background(cub3d->image, C_BACKGROUND);
// 	y = 0;
// 	while (y < cub3d->map->y_max)
// 	{
// 		x = 0;
// 		while (x < cub3d->map->x_max)
// 		{
// 			cub3d_draw_down_and_to_the_right(cub3d, y, x);
// 			x++;
// 		}
// 		y++;
// 	}
// 	cub3d->redraw = false;
// }

// victim #2: replaced by map_iteration version
// void
// 	cub3d_colour(
// 		t_cub3d	*cub3d)
// {
// 	int		x;
// 	int		y;
// 	t_point	*point;

// 	y = 0;
// 	while (y < cub3d->map->y_max)
// 	{
// 		x = 0;
// 		while (x < cub3d->map->x_max)
// 		{
// 			point = &cub3d->map->original[y][x];
// 			point->colour = map_earth_colour(cub3d->map, point);
// 			cub3d->map->project[y][x].colour = point->colour;
// 			x++;
// 		}
// 		y++;
// 	}
// }

// victim #3: replaced by map_iteration version

// parse map and rotate point[x,y,z] values around 0rigin (same as cub3d_project)
// this one is for optimization, given the angle of rotation is constant
// cosin holds the calculated values for cos(cub3d.speed) and sin(cub3d.speed)
// void
// 	cub3d_project_optimized(
// 		t_cub3d	*cub3d)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (y < cub3d->map->y_max)
// 	{
// 		x = 0;
// 		while (x < cub3d->map->x_max)
// 		{
// 			point = &cub3d->map->project[y][x];
// 			if (cub3d->precalc.gamma || cub3d->precalc.beta || cub3d->precalc.alpha)
// 				point_rotate_precalculated(cub3d, point);
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (cub3d->spinlock == false)
// 		cub3d->precalc = (t_precalc){0, 0, 0};
// }

// victim #4: replaced by map_iteration version

// parse map and rotate point[x,y,z] values around [0,0,0]
// this function is only for variable angles
// void
// 	cub3d_project(
// 		t_cub3d	*cub3d)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (y < cub3d->map->y_max)
// 	{
// 		x = 0;
// 		while (x < cub3d->map->x_max)
// 		{
// 			point = &cub3d->map->project[y][x];
// 			if (cub3d->perspective.gamma)
// 				point_rotate_gamma(point, cub3d->perspective.gamma);
// 			if (cub3d->perspective.beta)
// 				point_rotate_beta(point, cub3d->perspective.beta);
// 			if (cub3d->perspective.alpha)
// 				point_rotate_alpha(point, cub3d->perspective.alpha);
// 			x++;
// 		}
// 		y++;
// 	}
// 	cub3d->perspective = (t_perspective){0, 0, 0};
// }

// victim #5: replaced by map_iteration version
// void
// 	cub3d_scale(
// 		t_cub3d	*cub3d)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	cub3d->offset.x *= cub3d->scale.diff;
// 	cub3d->offset.y *= cub3d->scale.diff;
// 	while (y < cub3d->map->y_max)
// 	{
// 		x = 0;
// 		while (x < cub3d->map->x_max)
// 		{
// 			point = &cub3d->map->project[y][x];
// 			point->x *= cub3d->scale.diff;
// 			point->y *= cub3d->scale.diff;
// 			point->z *= cub3d->scale.diff;
// 			x++;
// 		}
// 		y++;
// 	}
// 	cub3d->scale.diff = 1;
// }

// victim #6: replaced by map_iteration version
// void
// 	map_set_original(
// 		t_map	*map)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			map->project[y][x] = map->original[y][x];
// 			x++;
// 		}
// 		y++;
// 	}
// }

// victim #7: replaced by map_iteration version
// void
// 	map_fill_polar(
// 		t_map	*map)
// {
// 	int				y;
// 	int				x;
// 	t_point			*point;
// 	const double	longitude_incr = -2 * PI / (map->x_max);
// 	const double	latitude_in = PI / (map->y_max - 1);

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			point = &map->original[y][x];
// 			map->polar[y][x] = (t_point)
// 			{(longitude_incr * x),
// 				(latitude_in * y),
// 				(map->radius + point->z),
// 				point->colour};
// 			x++;
// 		}
// 		y++;
// 	}
// }

// victim #8: replaced by map_iteration version

// convert polar coordinates back to cartesian
// polar is t_point with {(x) beta angle, (y) gamma angle, (z) length}
// swap polar->y and polar->x for x= and y= for cool projection
// void
// 	map_set_polar(
// 		t_map	*map)
// {
// 	int			y;
// 	int			x;
// 	t_point		*polar;

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			polar = &map->polar[y][x];
// 			map->project[y][x] = (t_point)
// 			{((polar->z) * cos(polar->x) * sin(polar->y)),
// 				((polar->z) * sin(polar->x) * sin(polar->y)),
// 				((polar->z) * cos(polar->y)),
// 				polar->colour};
// 			x++;
// 		}
// 		y++;
// 	}
// }

// victim #9: replaced by map_iteration version
// void
// 	map_find_z_min_max(
// 		t_map	*map)
// {
// 	int	x;
// 	int	y;
// 	int	z_val;

// 	y = 0;
// 	map->z_min = 0;
// 	map->z_max = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			z_val = map->original[y][x].z;
// 			if (z_val < map->z_min)
// 				map->z_min = z_val;
// 			if (z_val > map->z_max)
// 				map->z_max = z_val;
// 			x++;
// 		}
// 		y++;
// 	}
// 	map->radius = (map->z_max - map->z_min) * 10;
// }
