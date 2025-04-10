/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:36 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 11:48:38 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	erase_image(void)
{
	int	y;
	int	x;

	mlx_resize_image(game()->image, game()->mlx->width, game()->mlx->height);
	y = 0;
	while (y < game()->mlx->height / 2)
	{
		x = 0;
		while (x < game()->mlx->width)
			mlx_put_pixel(game()->image, x++, y, game()->ceiling);
		y++;
	}
	while (y < game()->mlx->height)
	{
		x = 0;
		while (x < game()->mlx->width)
			mlx_put_pixel(game()->image, x++, y, game()->floor);
		y++;
	}
}

static void	calc_environment(int x, t_coordinates *coord)
{
	calc_ray_directions(x, coord);
	calc_delta_distance(coord);
	calc_player_position(coord);
}

static void	process_dda(t_coordinates *coord)
{
	while (game()->map[coord->mapY][coord->mapX] != '1')
	{
		if (coord->sideDistX < coord->sideDistY)
		{
			coord->sideDistX += coord->deltaDistX;
			coord->mapX += coord->stepX;
			coord->side = 0;
		}
		else
		{
			coord->sideDistY += coord->deltaDistY;
			coord->mapY += coord->stepY;
			coord->side = 1;
		}
	}
}

static void	calc_perpendicular_ray(t_coordinates *coord)
{	
	if (coord->side == 0)
		coord->perpWallDist = (coord->sideDistX - coord->deltaDistX);
	else
		coord->perpWallDist = (coord->sideDistY - coord->deltaDistY);
	coord->lineHeight = (int)(game()->mlx->height / coord->perpWallDist);
	coord->drawStart = -coord->lineHeight / 2 + game()->mlx->height / 2;
	coord->drawEnd = coord->lineHeight / 2 + game()->mlx->height / 2;
	if (coord->drawStart < 0)
		coord->drawStart = 0;
	if (coord->drawEnd > game()->mlx->height)
		coord->drawEnd = game()->mlx->height - 1;
}

void	render_loop(void *param)
{
	int	x;

	(void)param;
	erase_image();
	x = 0;
	while (x < game()->mlx->width)
	{
		calc_environment(x, game()->coord);
		process_dda(game()->coord);
		calc_perpendicular_ray(game()->coord);
		draw_wall(x, game()->coord);
		x++;
	}
}
