/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderizer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:40:15 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:00:20 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_ray_directions(int width_pixel, t_coordinates *coord)
{
	float	camera;

	camera = (2 * width_pixel / (float) game()->mlx->width - 1);
	coord->ray_dir_x = coord->dir_x + coord->plane_x * camera;
	coord->ray_dir_y = coord->dir_y + coord->plane_y * camera;
}

void	calc_delta_distance(t_coordinates *coord)
{
	if (coord->ray_dir_x == 0)
		coord->delta_dist_x = HUGE_VALF;
	else
		coord->delta_dist_x = fabs(1 / coord->ray_dir_x);
	if (coord->ray_dir_y == 0)
		coord->delta_dist_y = HUGE_VALF;
	else
		coord->delta_dist_y = fabs(1 / coord->ray_dir_y);
}

void	calc_player_position(t_coordinates *c)
{
	c->map_x = (int) c->pos_x;
	c->map_y = (int) c->pos_y;
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (c->pos_x - c->map_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - c->pos_x) * c->delta_dist_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (c->pos_y - c->map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - c->pos_y) * c->delta_dist_y;
	}
}
