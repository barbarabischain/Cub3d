/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:05:07 by babischa          #+#    #+#             */
/*   Updated: 2025/04/14 14:44:20 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_neighbor_valid(char **matrix, int i, int j)
{
	if (matrix[i][j] && (matrix[i][j] == '1' || matrix[i][j] == '0' \
		|| matrix[i][j] == 'N' || matrix[i][j] == 'S' || matrix[i][j] == 'E' \
		|| matrix[i][j] == 'W'))
		return (1);
	return (0);
}

void	check_borders(char **matrix, int i, int j)
{
	if (i == 0 || i == game()->max_y)
		manage_error("Error: Invalid map\n");
	if (!(matrix[i][j - 1] && is_neighbor_valid(matrix, i, j - 1)))
		manage_error("Error: Invalid map\n");
	if (!(matrix[i][j + 1] && is_neighbor_valid(matrix, i, j + 1)))
		manage_error("Error: Invalid map\n");
	if (!(matrix[i - 1][j - 1] && is_neighbor_valid(matrix, i - 1, j - 1)))
		manage_error("Error: Invalid map\n");
	if (!(matrix[i - 1][j + 1] && is_neighbor_valid(matrix, i - 1, j + 1)))
		manage_error("Error: Invalid map\n");
	if (!(matrix[i + 1][j - 1] && is_neighbor_valid(matrix, i + 1, j - 1)))
		manage_error("Error: Invalid map\n");
	if (!(matrix[i + 1][j + 1] && is_neighbor_valid(matrix, i + 1, j + 1)))
		manage_error("Error: Invalid map\n");
}

void	validate_walls(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '0' || matrix[i][j] == 'N' || matrix[i][j] == 'S' || matrix[i][j] == 'E' || matrix[i][j] == 'W')
				check_borders(matrix, i, j);
			j++;
		}
		i++;
	}
}
