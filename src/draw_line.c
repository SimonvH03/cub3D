/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/16 00:20:34 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static uint32_t
	draw_line_colour(
		const t_line *line)
{
	double	relative_height;
	double	total_height;
	double	ratio;

	if (line->d_ctl > line->d_pas)
	{
		total_height = line->d_ctl;
		relative_height = line->i;
	}
	else
	{
		total_height = line->d_pas;
		relative_height = line->j;
	}
	if (relative_height == 0 || total_height == 0)
		return (line->p0->colour);
	ratio = relative_height / total_height;
	return (gradient(ratio, line->p0->colour, line->p1->colour));
}

static void
	draw_line_pixel(
		const t_cub3d *cub3d,
		const t_line *line)
{
	int	x_pixel;
	int	y_pixel;

	if (line->swapped == false)
	{
		x_pixel = line->p0->x + (line->i * line->s_ctl);
		y_pixel = line->p0->y + (line->j * line->s_pas);
	}
	else
	{
		x_pixel = line->p0->x + (line->j * line->s_pas);
		y_pixel = line->p0->y + (line->i * line->s_ctl);
	}
	if (!draw_check_point(cub3d, x_pixel, y_pixel))
		mlx_put_pixel(cub3d->image,
			x_pixel + cub3d->center.x + cub3d->offset.x,
			y_pixel + cub3d->center.y + cub3d->offset.y,
			draw_line_colour(line));
}

static int
	draw_straight_line(
		const t_cub3d *cub3d,
		t_line *line)
{
	if (line->d_pas == 0)
	{
		while (line->i <= line->d_ctl)
		{
			draw_line_pixel(cub3d, line);
			line->i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

// from draw.c / draw_orthogonally_adjacent()
void
	draw_line(
		const t_cub3d *cub3d,
		const t_point *p0,
		const t_point *p1)
{
	t_line	line;

	draw_line_init(&line, p0, p1);
	if (over_the_horizon(cub3d, &line) == EXIT_FAILURE)
		return ;
	if (draw_straight_line(cub3d, &line) == EXIT_SUCCESS)
		return ;
	while (line.i != line.d_ctl)
	{
		draw_line_pixel(cub3d, &line);
		if (line.err >= 0)
		{
			draw_line_pixel(cub3d, &line);
			line.j += 1;
			line.err -= line.d_ctl;
		}
		line.i += 1;
		line.err += line.d_pas;
	}
	draw_line_pixel(cub3d, &line);
}
