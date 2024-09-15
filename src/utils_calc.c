/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 19:23:25 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/// @brief 
/// @param x_minus_a X-center minus x-coordinate of point to check
/// @param y_minus_b Y-center minus y_coordinate of point to check
/// @param radius radius of circle
/// @return true(1) if point is inside the circle, false(0) if not
short
	is_in_circle(
		float x_minus_a,
		float y_minus_b,
		float radius)
{
	float	square_distance;

	square_distance = (x_minus_a) * (x_minus_a) + (y_minus_b) * (y_minus_b);
	if (radius * radius > square_distance)
		return (true);
	return (false);
}

// return highest value
float
	ft_max_float(
		float a,
		float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

// return lowest value
float
	ft_min_float(
		float a,
		float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// return absolute value
float
	ft_abs_float(
		float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

// return polarity of value
short
	ft_sign_float(
		float value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}
