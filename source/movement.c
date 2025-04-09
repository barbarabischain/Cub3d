/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:56 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/09 14:05:32 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_next_pos(float *nextPosX, float *nextPosY)
{
	float	spd;

	spd = game()->mlx->delta_time * 7.0;
	if (game()->key_w)
	{
		*nextPosX = (game()->coord->posX + game()->coord->dirX * spd);
		*nextPosY = (game()->coord->posY + game()->coord->dirY * spd);
	}
	if (game()->key_s)
	{	
		*nextPosX = (game()->coord->posX - game()->coord->dirX * spd);
		*nextPosY = (game()->coord->posY - game()->coord->dirY * spd);
	}
	if (game()->key_a)
	{
		*nextPosX = (game()->coord->posX - game()->coord->planeX * spd);
		*nextPosY = (game()->coord->posY - game()->coord->planeY * spd);
	}
	if (game()->key_d)
	{
		*nextPosX = game()->coord->posX + game()->coord->planeX * spd;
		*nextPosY = game()->coord->posY + game()->coord->planeY * spd;
	}
}

void	rotate(char dir)
{
	float			spd;
	float			backup;
	t_coordinates	*crd;

	crd = game()->coord;
	spd = game()->mlx->delta_time * 3.0;
	backup = crd->dirY;
	crd->dirY = crd->dirY * cos(spd * dir) - crd->dirX * sin (spd * dir);
	crd->dirX = backup * sin(spd * dir) + crd->dirX * cos(spd * dir);
	backup = crd->planeY;
	crd->planeY = crd->planeY * cos(spd * dir) - crd->planeX * sin(spd * dir);
	crd->planeX = backup * sin(spd * dir) + crd->planeX * cos(spd * dir);
}

void	new_movement(void *param)
{
	float	next_pos_x;
	float	next_pos_y;

	(void) param;
	next_pos_x = game()->coord->posX;
	next_pos_y = game()->coord->posY;
	calc_next_pos(&next_pos_x, &next_pos_y);
	if (game()->map[(int) game()->coord->posY][(int) next_pos_x] != '1')
		game()->coord->posX = next_pos_x;
	if (game()->map[(int) next_pos_y][(int) game()->coord->posX] != '1')
		game()->coord->posY = next_pos_y;
	if (game()->key_right)
		rotate(-1);
	if (game()->key_left)
		rotate(1);
}
