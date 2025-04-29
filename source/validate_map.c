/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:18:33 by babischa          #+#    #+#             */
/*   Updated: 2025/04/29 11:18:19 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_players(char **matrix)
{
	int		player;
	char	*line;

	player = 0;
	while (*matrix)
	{
		line = *matrix;
		while (*line)
		{
			if (player && is_player(*line))
				manage_error("Error: too many players\n");
			else if (!player && is_player(*line))
				player = 1;
			line++;
		}
		matrix++;
	}
	if (player == 0)
		manage_error("Error: player not found!\n");
}

void	validate_characters(char **matrix)
{
	char	*line;

	while (*matrix)
	{
		line = *matrix;
		while (*line)
		{
			if (!(is_player(*line) || *line == '1' \
			|| *line == '0' || ft_isspace(*line) || *line == '\n'))
				manage_error("Error: Invalid character\n");
			line++;
		}
		matrix++;
	}
}

void	validate_map_end(char **matrix)
{
	int	map_ended;

	map_ended = 0;
	while (*matrix && map_ended == 0)
	{
		if (ft_strlen(*matrix) == 1 && **matrix == '\n')
			map_ended = 1;
		matrix++;
	}
	if (*matrix && ft_strlen(*matrix) > 1 && map_ended)
		manage_error("Error: Invalid map\n");
}

void	validate_map(void)
{
	validate_players(game()->map);
	validate_characters(game()->map);
	validate_walls(game()->map);
	validate_map_end(game()->map);
}

void	replace_spaces_and_tabs(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (ft_isspace(matrix[i][j]))
			matrix[i][j] = ' ';
			j++;
		}
		i++;
	}
}
