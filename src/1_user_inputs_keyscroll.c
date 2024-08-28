/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_user_inputs_keyscroll.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/28 20:21:16 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from main.c / loop_hooks()
void
	keyhook(
		mlx_key_data_t keydata,
		void *param)
{
	t_window	*window;

	window = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(window->mlx);
	}
}

// void
// 	scrollhook(
// 		double xdelta,
// 		double ydelta,
// 		void *param)
// {
// 	t_window	*window;

// 	window = param;
// }
