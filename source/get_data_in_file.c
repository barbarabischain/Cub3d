/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_in_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:43 by babischa          #+#    #+#             */
/*   Updated: 2025/03/17 19:33:20 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	search_in_file(char *line)
{
	if (!ft_strncmp("NO", line, 2))
		handle_texture(line, &game()->textures->north_path);
	else if (!ft_strncmp("SO", line, 2))
		handle_texture(line, &game()->textures->south_path);
	else if (!ft_strncmp("WE", line, 2))
		handle_texture(line, &game()->textures->west_path);
	else if (!ft_strncmp("EA", line, 2))
		handle_texture(line, &game()->textures->east_path);
	else if (!ft_strncmp("F", line, 1))
		handle_color(line, &game()->floor1);
	else if (!ft_strncmp("C", line, 1))
		handle_color(line, &game()->ceiling1);
	//else if (ft_strncmp("1", line, 1))
	//	handle_map(line);
}

void	get_data_in_file(int fd)
{
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		while(ft_isspace(*tmp))
			tmp++;
		if (*tmp != '\0' && *tmp != '\n')
			search_in_file(tmp);
		free(line);
		line = get_next_line(fd);
	}
	//check_data(); verificar se os dados foram corretamente inseridos
}
