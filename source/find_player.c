/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:07:57 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/07 15:46:35 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_camera_inital_pos(char c)
{
	if (c == 'N')
	{
		game()->coord->dirX = 0;
		game()->coord->dirY = -1;
		game()->coord->planeX = 0.66;
		game()->coord->planeY = 0;
	}
	else if (c == 'S')
	{
		game()->coord->dirX = 0;
		game()->coord->dirY = 1;
		game()->coord->planeX = -0.66;
		game()->coord->planeY = 0;
	}
	else if (c == 'E')
	{
		game()->coord->dirX = 1;
		game()->coord->dirY = 0;
		game()->coord->planeX = 0.0;
		game()->coord->planeY = 0.66;
	}
	else
	{
		game()->coord->dirX = -1.0;
		game()->coord->dirY = 0;
		game()->coord->planeX = 0.0;
		game()->coord->planeY = -0.66;
	}
}

void	set_player_initial_pos(void)
{
	int	x;
	int	y;
	
	y = 1;
	while (y < MAX_Y)
	{
		x = 1;
		while (x < MAX_X)
		{
			if (ft_strchr("NSWE", game()->map[y][x]))
			{
				game()->coord->posX = x;
				game()->coord->posY = y;
				set_camera_inital_pos(game()->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	} 
}