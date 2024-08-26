/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cycle_palettes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:05:29 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from user_inputs_keyscroll.c / keyhook()
t_palette	map_cycle_palettes(t_map *map)
{
	if (map->palette.nr == P_RGB_NR)
		return ((t_palette){P_HACKERMAN_NR, C_HACKERMAN_BACK,
			C_HACKERMAN_LOW, C_HACKERMAN_MID, C_HACKERMAN_HIGH});
	else if (map->palette.nr == P_HACKERMAN_NR)
		return ((t_palette){P_METAL_NR, C_METAL_BACK,
			C_METAL_LOW, C_METAL_MID, C_METAL_HIGH});
	else if (map->palette.nr == P_METAL_NR)
		return ((t_palette){P_RUST_NR, C_RUST_BACK,
			C_RUST_LOW, C_RUST_MID, C_RUST_HIGH});
	else if (map->palette.nr == P_RUST_NR)
		return ((t_palette){P_EARTH_NR, C_EARTH_BACK, 0, 0, 0});
	else
		return ((t_palette){P_RGB_NR, C_RGB_BACK,
			C_RGB_LOW, C_RGB_MID, C_RGB_HIGH});
}
