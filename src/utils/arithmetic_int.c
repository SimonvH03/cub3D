/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmetic_int.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 01:32:56 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_clamp(int a, int lower_bound, int upper_bound)
{
	if (a < lower_bound)
		return (lower_bound);
	if (a > upper_bound)
		return (upper_bound);
	return (a);
}

// return lowest value
int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
