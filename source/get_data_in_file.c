/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_in_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:43 by babischa          #+#    #+#             */
/*   Updated: 2025/03/17 11:50:41 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	printf("fd: %d path: %s\n", fd, path);
	if (fd == -1)
		return (0);
	close (fd);
	return (1);
}

void	handle_texture(char *line, char **texture)
{
	char	**split_path;
	char	*trim_path;

	if (*texture != NULL)
	{
		free(line);
		manage_error("Error: duplicate texture!\n");
	}
	split_path = ft_split(line, ' ');
	if (!split_path || !split_path[0] || !split_path[1])
	{
		free(line);
		free_matrix(split_path);
		manage_error("Error: invalid path1!\n");
	}
	trim_path = ft_strtrim(split_path[1], "\n\t\b\v\r");
	free_matrix(split_path);
	if (!is_valid_path(trim_path))
	{
		free(line);
		manage_error("Error: invalid path2!\n");
	}
	*texture = ft_strdup(trim_path);
	free(trim_path);
}

void	search_in_file(char *line)
{
	if (!ft_strncmp("NO", line, 2))
		handle_texture(line, &game()->textures->north_path);
	else if (!ft_strncmp("SO", line, 2))
		handle_texture(line, &game()->textures->south_path);
	else if (!ft_strncmp("WE", line, 2))
		handle_texture(line, &game()->textures->west_path);
	else if (!ft_strncmp("EA", line, 2))
		handle_texture(line, &game()->textures->east_path);ls -a
	// else if (ft_strncmp("F", line, 1))
	// 	handle_colors(line);
	// else if (ft_strncmp("C", line, 1))
	//	handle_colors(line);
	//else if (ft_strncmp("1", line, 1))
	//	handle_map(line);
}

void	get_data_in_file(int fd)
{
	char	*tmp;
	char	*line;

	tmp = get_next_line(fd);
	while (tmp)
	{
		line = tmp;
		search_in_file(tmp);
		free(line);
		tmp = get_next_line(fd);
	}
	load_textures();
	//check_data(); verificar se os dados foram corretamente inseridos
}
