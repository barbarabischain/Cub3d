/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_in_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:43 by babischa          #+#    #+#             */
/*   Updated: 2025/04/25 18:51:46 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_data(void)
{
	if (!game()->textures->north_path)
		return (0);
	if (!game()->textures->south_path)
		return (0);
	if (!game()->textures->east_path)
		return (0);
	if (!game()->textures->west_path)
		return (0);
	if (!game()->ceiling)
		return (0);
	if (!game()->floor)
		return (0);
	if (!game()->map)
		return (0);
	return (1);
}

void	get_textures_colors(char *line, int start, int fd)
{	
	char	*tmp;

	tmp = line + start;
	if (!ft_strncmp("NO", tmp, 2))
		handle_texture(line, &game()->textures->north_path, fd);
	else if (!ft_strncmp("SO", tmp, 2))
		handle_texture(line, &game()->textures->south_path, fd);
	else if (!ft_strncmp("WE", tmp, 2))
		handle_texture(line, &game()->textures->west_path, fd);
	else if (!ft_strncmp("EA", tmp, 2))
		handle_texture(line, &game()->textures->east_path, fd);
	else if (!ft_strncmp("F", tmp, 1))
		handle_color(line, &game()->floor, fd);
	else if (!ft_strncmp("C", tmp, 1))
		handle_color(line, &game()->ceiling, fd);
	else
	{
		free(line);
		finish_get_line(fd);
		manage_error("ERROR: Invalid character!\n");
	}
}

void	get_data_in_file(int fd)
{
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		while (ft_isspace(*tmp))
			tmp++;
		if (!ft_strncmp(tmp, "1", 1) || !ft_strncmp(tmp, "0", 1))
		{
			get_map(line, fd);
			break ;
		}
		else if (*tmp != '\0' && *tmp != '\n')
			get_textures_colors(line, tmp - line, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (!check_data())
		manage_error("Error: Missing data in file.\n");
}
