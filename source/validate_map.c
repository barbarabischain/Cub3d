/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:18:33 by babischa          #+#    #+#             */
/*   Updated: 2025/04/17 10:19:18 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

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
			|| *line == '0' || *line == ' ' || *line == '\n'))
				manage_error("Error: Invalid character");
			line++;
		}
		matrix++;
	}
}

// void	validate_map_end(char **matrix)
// {

// }

void	validate_map(void)
{
	validate_players(game()->map);
	validate_characters(game()->map);
	validate_walls(game()->map);
	// validate_end(game()->map);
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
