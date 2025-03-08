/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:56 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/21 12:08:19 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int MAP_b[MAX_Y][MAX_X] = {
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

void	movement(void *param)
{
	t_game	*data;
	double	moveSpeed;
	double	rotSpeed;

	data = (t_game *)param;
	moveSpeed = data->mlx->delta_time * 5.0;
	rotSpeed = data->mlx->delta_time * 3.0;
	if (data->key_w)
	{
		if(MAP_b[(int) (data->coord->posX + data->coord->dirX * moveSpeed)][(int)data->coord->posY] == false) 
			data->coord->posX += data->coord->dirX * moveSpeed;
      	if(MAP_b[(int) data->coord->posX][(int) (data->coord->posY + data->coord->dirY * moveSpeed)] == false) 
			data->coord->posY += data->coord->dirY * moveSpeed;
	}
	if (data->key_s)
	{
		if(MAP_b[(int) (data->coord->posX + data->coord->dirX * moveSpeed)][(int)data->coord->posY] == false) 
			data->coord->posX -= data->coord->dirX * moveSpeed;
      	if(MAP_b[(int) data->coord->posX][(int) (data->coord->posY + data->coord->dirY * moveSpeed)] == false) 
			data->coord->posY -= data->coord->dirY * moveSpeed;
	}
	if (data->key_d)
	{
		double oldDirX = data->coord->dirX;
		data->coord->dirX = data->coord->dirX * cos(-rotSpeed) - data->coord->dirY * sin(-rotSpeed);
		data->coord->dirY = oldDirX * sin(-rotSpeed) + data->coord->dirY * cos(-rotSpeed);
		double oldPlaneX = data->coord->planeX;
		data->coord->planeX = data->coord->planeX * cos(-rotSpeed) - data->coord->planeY * sin(-rotSpeed);
		data->coord->planeY = oldPlaneX * sin(-rotSpeed) + data->coord->planeY * cos(-rotSpeed);
	}
	if (data->key_a)
	{
		double oldDirX = data->coord->dirX;
		data->coord->dirX = data->coord->dirX * cos(rotSpeed) - data->coord->dirY * sin(rotSpeed);
		data->coord->dirY = oldDirX * sin(rotSpeed) + data->coord->dirY * cos(rotSpeed);
		double oldPlaneX = data->coord->planeX;
		data->coord->planeX = data->coord->planeX * cos(rotSpeed) - data->coord->planeY * sin(rotSpeed);
		data->coord->planeY = oldPlaneX * sin(rotSpeed) + data->coord->planeY * cos(rotSpeed);
	}
}