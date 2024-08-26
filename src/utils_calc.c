/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// turn degree angle into radian
double
	deg_to_rad(
		double angle_deg)
{
	return (angle_deg * PI / 180);
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
