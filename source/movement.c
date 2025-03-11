/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:56 by madias-m          #+#    #+#             */
/*   Updated: 2025/03/11 16:34:09 by madias-m         ###   ########.fr       */
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

void	calc_next_pos(double *nextPosX, double *nextPosY)
{
	double moveSpeed;

	moveSpeed = game()->mlx->delta_time * 5.0;
	if (game()->key_w)
	{
		*nextPosX = (game()->coord->posX + game()->coord->dirX * moveSpeed);
		*nextPosY = (game()->coord->posY + game()->coord->dirY * moveSpeed);
	}
	if (game()->key_s)
	{	
		*nextPosX = (game()->coord->posX - game()->coord->dirX * moveSpeed);
		*nextPosY = (game()->coord->posY - game()->coord->dirY * moveSpeed);
	}
	if (game()->key_a)
	{
		*nextPosX = (game()->coord->posX - game()->coord->planeX * moveSpeed);
		*nextPosY = (game()->coord->posY - game()->coord->planeY * moveSpeed);
	}
	if (game()->key_d)
	{
		*nextPosX = game()->coord->posX + game()->coord->planeX * moveSpeed;
		*nextPosY = game()->coord->posY + game()->coord->planeY * moveSpeed;
	}
}

void	rotate_camera(char dir)
{
	double	rotSpeed;
	double	backup;
	t_coordinates	*coord;
	
	coord = game()->coord;
	rotSpeed = game()->mlx->delta_time * 3.0;
	backup = coord->dirX;
	coord->dirX = coord->dirX * cos(rotSpeed * dir) - coord->dirY * sin(rotSpeed * dir);
	coord->dirY = backup * sin(rotSpeed * dir) + coord->dirY * cos(rotSpeed * dir);
	backup = coord->planeX;
	coord->planeX = coord->planeX * cos(rotSpeed * dir) - coord->planeY * sin(rotSpeed * dir);
	coord->planeY = backup * sin(rotSpeed * dir) + coord->planeY * cos(rotSpeed * dir);
}

void	new_movement(void * param)
{
	double nextPosX;
	double nextPosY;
	
	(void) param;
	nextPosX = 0;
	nextPosY = 0;
	calc_next_pos(&nextPosX, &nextPosY);
	if (MAP_b[(int) game()->coord->posX][(int) nextPosY] == 0)
		game()->coord->posY = nextPosY;
	if (MAP_b[(int) nextPosX][(int) game()->coord->posY] == 0)
		game()->coord->posX = nextPosX;
	if (game()->key_right)
		rotate_camera(-1);
	if (game()->key_left)
		rotate_camera(1);	
}