/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/23 02:13:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void
	update_health_bar(
		t_health_bar *health_bar,
		float new_health)
{
	health_bar->current_health = ft_min_float(new_health, health_bar->max_health);
	health_bar->current_health = ft_max_float(health_bar->current_health, 0.0f);
}

void
	draw_health_bar(
		t_health_bar *health_bar)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	health_width;
	uint32_t	*pixels;

	pixels = (uint32_t *)health_bar->image->pixels;
	health_width = (uint32_t)(health_bar->width * 
		(health_bar->current_health / health_bar->max_health));

	y = 0;
	while (y < health_bar->height)
	{
		x = 0;
		while (x < health_bar->width)
		{
			if (x < health_width)
				pixels[y * health_bar->width + x] = 0xFF00FF00; // Green (B=0, G=255, R=0, A=255)
			else
				pixels[y * health_bar->width + x] = 0xFF0000FF; // Red (B=0, G=0, R=255, A=255)
			x++;
		}
		y++;
	}
} 