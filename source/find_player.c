/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:07:57 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/07 15:25:51 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
				return ;
			}
			x++;
		}
		y++;
	} 
}