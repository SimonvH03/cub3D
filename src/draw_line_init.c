/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool
	line_swap_control_axis(
		t_line *line)
{
	int	temp;

	if (line->d_ctl >= line->d_pas)
		return (false);
	temp = line->d_ctl;
	line->d_ctl = line->d_pas;
	line->d_pas = temp;
	temp = line->s_ctl;
	line->s_ctl = line->s_pas;
	line->s_pas = temp;
	return (true);
}

// from draw_line.c / draw_line()
void
	draw_line_init(
		t_line *line,
		const t_point *p0,
		const t_point *p1)
{
	line->d_ctl = ft_abs_double(p1->x - p0->x);
	line->d_pas = ft_abs_double(p1->y - p0->y);
	line->s_ctl = ft_sign_double(p1->x - p0->x);
	line->s_pas = ft_sign_double(p1->y - p0->y);
	line->swapped = line_swap_control_axis(line);
	line->p0 = p0;
	line->p1 = p1;
	line->i = 0;
	line->j = 0;
	line->err = line->d_pas - line->d_ctl - line->s_ctl;
}
