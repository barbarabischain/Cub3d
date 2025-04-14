/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:01:20 by babischa          #+#    #+#             */
/*   Updated: 2025/04/14 17:28:01 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	convert_color(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	color_error(char **matrix, char *line)
{
	if (matrix)
		free_matrix(matrix);
	if (line)
		free(line);
	manage_error("Error: Invalid color!\n");
}

int	is_valid_color(char	*rgb_element)
{
	while (*rgb_element)
	{
		if (!ft_isdigit(*rgb_element))
			return (0);
		rgb_element++;
	}
	return (1);
}

char	**process_line(char	*line)
{
	char	*trim_line;
	char	**rgb;

	rgb = NULL;
	trim_line = ft_strtrim(line, "FC \t\v\f\r\n\b");
	rgb = ft_split(trim_line, ',');
	free(trim_line);
	if ((!rgb || !rgb[0] || !rgb[1] || !rgb[2]))
		color_error(rgb, line);
	return (rgb);
}

void	handle_color(char *line, uint32_t *color)
{
	char	**rgb;
	char	*tmp;
	int		i;

	rgb = NULL;
	if (*color != (uint32_t)-42)
		color_error(rgb, line);
	rgb = process_line(line);
	i = 0;
	while (rgb[i])
	{
		tmp = ft_strtrim(rgb[i], " \t\v\f\n\b");
		if (!is_valid_color(tmp))
		{
			free(tmp);
			color_error(rgb, line);
		}
		i++;
		free(tmp);
	}
	*color = convert_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_matrix(rgb);
}
