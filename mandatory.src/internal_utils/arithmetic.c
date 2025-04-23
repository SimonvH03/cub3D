/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmetic_float.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 01:34:33 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

// return absolute value
float	ft_abs_float(float value)
{
	if (value < 0)
		return (-value);
	return (value);
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

// return lowest value
int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
