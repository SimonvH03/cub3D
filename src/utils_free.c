/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from main.c / main()
int
	scene_free(
		t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->y_max && scene->map && scene->map[i])
		free(scene->map[i++]);
	free(scene->map);
	return (EXIT_FAILURE);
}
