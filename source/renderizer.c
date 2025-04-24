/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:36 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/24 12:06:40 by madias-m         ###   ########.fr       */
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
	while (game()->map[coord->map_y][coord->map_x] != '1')
	{
		if (coord->side_dist_x < coord->side_dist_y)
		{
			coord->side_dist_x += coord->delta_dist_x;
			coord->map_x += coord->step_x;
			coord->side = 0;
		}
		else
		{
			coord->side_dist_y += coord->delta_dist_y;
			coord->map_y += coord->step_y;
			coord->side = 1;
		}
	}
}

static void	calc_perpendicular_ray(t_coordinates *coord)
{	
	if (coord->side == 0)
		coord->perp_wall_dist = (coord->side_dist_x - coord->delta_dist_x);
	else
		coord->perp_wall_dist = (coord->side_dist_y - coord->delta_dist_y);
	coord->line_height = (int)(game()->mlx->height / coord->perp_wall_dist);
	coord->draw_start = -coord->line_height / 2 + game()->mlx->height / 2;
	coord->draw_end = coord->line_height / 2 + game()->mlx->height / 2;
	if (coord->draw_start < 0)
		coord->draw_start = 0;
	if (coord->draw_end > game()->mlx->height)
		coord->draw_end = game()->mlx->height - 1;
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
