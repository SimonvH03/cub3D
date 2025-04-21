/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   weapon_animation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 22:23:58 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_fire_weapon(t_weapon *weapon)
{
	if (weapon->fire[weapon->frame_id].image != NULL)
	{
		modlx_imgcpy(weapon->display_img,
			weapon->fire[weapon->frame_id].image);
	}
	else
	{
		modlx_imgcpy(weapon->display_img,
			weapon->rest.image);
		weapon->state = ws_idle;
		weapon->frame_id = -1;
	}
}

static void	update_reload_weapon(t_weapon *weapon)
{
	if (weapon->reload[weapon->frame_id].image != NULL)
	{
		modlx_imgcpy(weapon->display_img,
			weapon->reload[weapon->frame_id].image);
	}
	else
	{
		modlx_imgcpy(weapon->display_img,
			weapon->rest.image);
		weapon->state = ws_idle;
		weapon->ammo = ft_min_int(weapon->mag_capacity, weapon->total_ammo);
		weapon->total_ammo -= weapon->ammo;
		weapon->frame_id = -1;
	}
}

void
	update_weapon(
		mlx_t *mlx,
		t_weapon *weapon)
{
	if (weapon->state == ws_idle)
		return ;
	weapon->frame_time += mlx->delta_time;
	if (weapon->frame_time < weapon->frame_time_goal)
		return ;
	weapon->frame_time = 0;
	weapon->frame_id++;
	if (weapon->state == ws_firing)
		update_fire_weapon(weapon);
	if (weapon->state == ws_reloading)
		update_reload_weapon(weapon);
}

void	fire_weapon(t_weapon *weapon)
{
	if (weapon->state != ws_idle || weapon->ammo == 0)
		return ;
	weapon->state = ws_firing;
	weapon->ammo--;
}

void	reload_weapon(t_weapon *weapon)
{
	if (weapon->state != ws_idle || weapon->ammo == weapon->mag_capacity)
		return ;
	weapon->state = ws_reloading;
	weapon->total_ammo += weapon->ammo;
	weapon->ammo = 0;
}
