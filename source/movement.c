/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:56 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 12:58:45 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_next_pos(float *nextPosX, float *nextPosY)
{
	float	spd;

	spd = game()->mlx->delta_time * 7.0;
	if (game()->key_w)
	{
		*nextPosX = (game()->coord->pos_x + game()->coord->dir_x * spd);
		*nextPosY = (game()->coord->pos_y + game()->coord->dir_y * spd);
	}
	if (game()->key_s)
	{	
		*nextPosX = (game()->coord->pos_x - game()->coord->dir_x * spd);
		*nextPosY = (game()->coord->pos_y - game()->coord->dir_y * spd);
	}
	if (game()->key_a)
	{
		*nextPosX = (game()->coord->pos_x - game()->coord->plane_x * spd);
		*nextPosY = (game()->coord->pos_y - game()->coord->plane_y * spd);
	}
	if (game()->key_d)
	{
		*nextPosX = game()->coord->pos_x + game()->coord->plane_x * spd;
		*nextPosY = game()->coord->pos_y + game()->coord->plane_y * spd;
	}
}

void	rotate(char dir)
{
	float			spd;
	float			backup;
	t_coordinates	*crd;

	crd = game()->coord;
	spd = game()->mlx->delta_time * 3.0;
	backup = crd->dir_y;
	crd->dir_y = crd->dir_y * cos(spd * dir) - crd->dir_x * sin (spd * dir);
	crd->dir_x = backup * sin(spd * dir) + crd->dir_x * cos(spd * dir);
	backup = crd->plane_y;
	crd->plane_y = crd->plane_y * cos(spd * dir) - crd->plane_x * sin(spd * dir);
	crd->plane_x = backup * sin(spd * dir) + crd->plane_x * cos(spd * dir);
}

void	new_movement(void *param)
{
	float	next_pos_x;
	float	next_pos_y;

	(void) param;
	next_pos_x = game()->coord->pos_x;
	next_pos_y = game()->coord->pos_y;
	calc_next_pos(&next_pos_x, &next_pos_y);
	if (game()->map[(int) game()->coord->pos_y][(int) next_pos_x] != '1')
		game()->coord->pos_x = next_pos_x;
	if (game()->map[(int) next_pos_y][(int) game()->coord->pos_x] != '1')
		game()->coord->pos_y = next_pos_y;
	if (game()->key_right)
		rotate(-1);
	if (game()->key_left)
		rotate(1);
}
