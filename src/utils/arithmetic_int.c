/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmetic_int.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/20 02:26:00 by simon         ########   odam.nl         */
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

// return highest value
int	ft_max_int(int a, int b)
{
	if (a < b)
		return (b);
	else
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

// return absolute value
int	ft_abs_int(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

// return polarity of value
short	ft_sign_int(int value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}
