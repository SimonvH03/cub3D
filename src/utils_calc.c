/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/29 14:17:32 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// turn degree angle into radian
float
	deg_to_rad(
		float angle_deg)
{
	return (angle_deg * (float)(PI / 180));
}

// return highest value
float
	ft_max_float(
		float a,
		float b)
{
	if (a >= b)
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
