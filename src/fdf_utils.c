/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// used by cub3d_init(), keyhook() and user_input_presets.c
// puts the 'origin' back into the middle of the window
void
	cub3d_center_offset(
		t_cub3d *cub3d)
{
	cub3d->center.x = cub3d->image->width / 2;
	cub3d->center.y = cub3d->image->height / 2;
	cub3d->offset.x = 0;
	cub3d->offset.y = 0;
}
