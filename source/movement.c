/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:56 by madias-m          #+#    #+#             */
/*   Updated: 2025/03/14 20:59:56 by madias-m         ###   ########.fr       */
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
	double	spd;

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

void	rotate_camera(char dir)
{
	double			spd;
	double			backup;
	t_coordinates	*crd;

	crd = game()->coord;
	spd = game()->mlx->delta_time * 3.0;
	backup = crd->dirX;
	crd->dirX = crd->dirX * cos(spd * dir) - crd->dirY * sin(spd * dir);
	crd->dirY = backup * sin(spd * dir) + crd->dirY * cos(spd * dir);
	backup = crd->planeX;
	crd->planeX = crd->planeX * cos(spd * dir) - crd->planeY * sin(spd * dir);
	crd->planeY = backup * sin(spd * dir) + crd->planeY * cos(spd * dir);
}

void	new_movement(void *param)
{
	double	next_pos_x;
	double	next_pos_y;

	(void) param;
	next_pos_x = 0;
	next_pos_y = 0;
	calc_next_pos(&next_pos_x, &next_pos_y);
	if (MAP_b[(int) game()->coord->posX][(int) next_pos_y] == 0)
		game()->coord->posY = next_pos_y;
	if (MAP_b[(int) next_pos_x][(int) game()->coord->posY] == 0)
		game()->coord->posX = next_pos_x;
	if (game()->key_right)
		rotate_camera(-1);
	if (game()->key_left)
		rotate_camera(1);
}
