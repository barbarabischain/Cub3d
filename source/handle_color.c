/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:01:20 by babischa          #+#    #+#             */
/*   Updated: 2025/04/28 11:01:06 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	convert_color(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	color_error(char **matrix, char *line, int fd)
{
	if (matrix)
		free_matrix(matrix);
	if (line)
		free(line);
	finish_get_line(fd);
	manage_error("Error: Invalid color!\n");
}

int	is_valid_color(char	*rgb_element)
{
	int	i;
	int	value;

	i = 0;
	while (rgb_element[i])
	{
		if (!ft_isdigit(rgb_element[i]))
			return (0);
		i++;
	}
	value = ft_atoi(rgb_element);
	if (value > 255 || value < 0)
		return (0);
	return (1);
}

char	**process_line(char	*line, int fd)
{
	char	*trim_line;
	char	**rgb;

	rgb = NULL;
	if (count_comma(line) != 2)
		color_error(rgb, line, fd);
	trim_line = ft_strtrim(line, "FC \t\v\f\r\n\b");
	rgb = ft_split(trim_line, ',');
	free(trim_line);
	if ((!rgb || !rgb[0] || !rgb[1] || !rgb[2]))
		color_error(rgb, line, fd);
	return (rgb);
}

void	handle_color(char *line, uint32_t *color, int fd)
{
	char	**rgb;
	char	*tmp;
	int		i;

	rgb = process_line(line, fd);
	i = 0;
	while (rgb[i])
	{
		tmp = ft_strtrim(rgb[i], " \t\v\f\n\b");
		if (!is_valid_color(tmp))
		{
			free(tmp);
			color_error(rgb, line, fd);
		}
		i++;
		free(tmp);
	}
	*color = convert_color(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_matrix(rgb);
}
