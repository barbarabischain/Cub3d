/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_in_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:43 by babischa          #+#    #+#             */
/*   Updated: 2025/03/18 17:17:05 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_textures_colors(char *tmp)
{
	if (!ft_strncmp("NO", tmp, 2))
		handle_texture(tmp, &game()->textures->north_path);
	else if (!ft_strncmp("SO", tmp, 2))
		handle_texture(tmp, &game()->textures->south_path);
	else if (!ft_strncmp("WE", tmp, 2))
		handle_texture(tmp, &game()->textures->west_path);
	else if (!ft_strncmp("EA", tmp, 2))
		handle_texture(tmp, &game()->textures->east_path);
	else if (!ft_strncmp("F", tmp, 1))
		handle_color(tmp, &game()->floor);
	else if (!ft_strncmp("C", tmp, 1))
		handle_color(tmp, &game()->ceiling);
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
			break;
		}
		else if (*tmp != '\0' && *tmp != '\n')
				get_textures_colors(tmp);
		free(line);
		line = get_next_line(fd);
	}
	//checar se todos os itens estão armazenados
	//load_textures();
}
