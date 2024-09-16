/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:01 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/16 16:34:33 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
