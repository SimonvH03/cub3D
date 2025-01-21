/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:45:23 by svan-hoo          #+#    #+#             */
/*   Updated: 2025/01/21 17:16:45 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
    clear_weapon_image(
        mlx_image_t *image)
{
    uint32_t    cy;
    uint32_t    cx;

    cy = 0;
    while (cy < image->height)
    {
        cx = 0;
        while (cx < image->width)
        {
            mlx_put_pixel(image, cx, cy, 0x00000000);
            cx++;
        }
        cy++;
    }
}

static void
    draw_pixel_block(
        mlx_image_t *image,
        uint32_t x,
        uint32_t y,
        uint32_t color)
{
    const int   pixel_size = 9;
    int         py;
    int         px;

    py = 0;
    while (py < pixel_size && (y + py) < image->height)
    {
        px = 0;
        while (px < pixel_size && (x + px) < image->width)
        {
            mlx_put_pixel(image, x + px, y + py, color);
            px++;
        }
        py++;
    }
} 