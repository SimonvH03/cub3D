/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:05:50 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 19:37:45 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from loop_hooks
void
	draw(
		void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (cub3d->redraw == false)
		return ;
	draw_background(cub3d->image, cub3d->scene);
	cub3d->redraw = false;
}
