/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:31:12 by babischa          #+#    #+#             */
/*   Updated: 2025/04/07 18:35:05 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int count_columns(char **matrix)
{
	int i;

	i = 0;
	while (*matrix)
	{
		if ((int)ft_strlen(*matrix) > i)
			i = (int)ft_strlen(*matrix);
		matrix++;
	}
	return (i - 1);
}

int	count_lines(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i - 1);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
