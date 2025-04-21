/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmetic_float.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 22:35:21 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	nearest_power_of_2(float value)
{
	if (value <= 0)
		return (0);
	return (powf(2.0f, roundf(log2f(value))));
}

// return absolute value
float	ft_abs_float(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

// return highest value
float	ft_max_float(float a, float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

// return lowest value
float	ft_min_float(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// return polarity of value
short	ft_sign_float(float value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}
