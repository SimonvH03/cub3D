/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/08 18:39:37 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// /// @brief 
// /// @param a x-coordinate of circle center
// /// @param b y-coordinate of circle center
// /// @param r radius of circle
// /// @param x x-coordinate of point to check
// /// @param y y_coordinate of point to check
// /// @return true(1) if point is inside the circle, false(0) if not
// short
// 	is_in_circle(
// 		double	a,
// 		double	b,
// 		double	r,
// 		double	x,
// 		double	y)
// {
// 	double	square_distance_to_center;

// 	square_distance_to_center = (x - a) * (x - a) + (y - b) * (y - b);
// 	if (r * r > square_distance_to_center)
// 		return (true);
// 	return (false);
// }

/// @brief 
/// @param x_minus_a X-center minus x-coordinate of point to check
/// @param y_minus_b Y-center minus y_coordinate of point to check
/// @param radius radius of circle
/// @return true(1) if point is inside the circle, false(0) if not
short
	is_in_circle(
		double x_minus_a,
		double y_minus_b,
		double radius)
{
	double	square_distance;

	square_distance = (x_minus_a) * (x_minus_a) + (y_minus_b) * (y_minus_b);
	if (radius * radius > square_distance)
		return (true);
	return (false);
}

// turn degree angle into radian
double
	deg_to_rad(
		double angle_deg)
{
	return (angle_deg * (double)(PI / 180));
}

// return highest value
double
	ft_max_double(
		double a,
		double b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

// return absolute value
double
	ft_abs_double(
		double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

// return polarity of value
short
	ft_sign_double(
		double value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}
