/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderizer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:40:15 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 11:48:55 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_ray_directions(int width_pixel, t_coordinates *coord)
{
	float	camera;

	camera = (2 * width_pixel / (float) game()->mlx->width - 1);
	coord->rayDirX = coord->dirX + coord->planeX * camera;
	coord->rayDirY = coord->dirY + coord->planeY * camera;
}

void	calc_delta_distance(t_coordinates *coord)
{
	if (coord->rayDirX == 0)
		coord->deltaDistX = HUGE_VALF;
	else
		coord->deltaDistX = fabs(1 / coord->rayDirX);
	if (coord->rayDirY == 0)
		coord->deltaDistY = HUGE_VALF;
	else
		coord->deltaDistY = fabs(1 / coord->rayDirY);
}

void	calc_player_position(t_coordinates *c)
{
	c->mapX = (int) c->posX;
	c->mapY = (int) c->posY;
	if (c->rayDirX < 0)
	{
		c->stepX = -1;
		c->sideDistX = (c->posX - c->mapX) * c->deltaDistX;
	}
	else
	{
		c->stepX = 1;
		c->sideDistX = (c->mapX + 1.0 - c->posX) * c->deltaDistX;
	}
	if (c->rayDirY < 0)
	{
		c->stepY = -1;
		c->sideDistY = (c->posY - c->mapY) * c->deltaDistY;
	}
	else
	{
		c->stepY = 1;
		c->sideDistY = (c->mapY + 1.0 - c->posY) * c->deltaDistY;
	}
}
