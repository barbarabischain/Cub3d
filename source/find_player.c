/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:07:57 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:06:51 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_dir(float x, float y)
{
	game()->coord->dir_x = x;
	game()->coord->dir_y = y;
}

static void	set_plane(float x, float y)
{
	game()->coord->plane_x = x;
	game()->coord->plane_y = y;
}

static void	set_camera_inital_pos(char c)
{
	if (c == 'N')
	{
		set_dir(0, -1);
		set_plane(0.66, 0);
	}
	else if (c == 'S')
	{
		set_dir(0, 1);
		set_plane(-0.66, 0);
	}
	else if (c == 'E')
	{
		set_dir(1, 0);
		set_plane(0, 0.66);
	}
	else
	{
		set_dir(-1, 0);
		set_plane(0, -0.66);
	}
}

void	set_player_initial_pos(void)
{
	int	x;
	int	y;

	y = 1;
	while (y < game()->max_y)
	{
		x = 1;
		while (x < game()->max_x)
		{
			if (ft_strchr("NSWE", game()->map[y][x]))
			{
				game()->coord->pos_x = x;
				game()->coord->pos_y = y;
				set_camera_inital_pos(game()->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}
