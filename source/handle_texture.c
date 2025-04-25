/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:22 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/25 16:53:33 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*load(char *texture_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_path);
	if (!texture)
		ft_printf("Failed to load texture: %s\n", texture_path);
	return (texture);
}

void	load_textures(void)
{
	game()->textures->north_tex = load(game()->textures->north_path);
	game()->textures->south_tex = load(game()->textures->south_path);
	game()->textures->east_tex = load(game()->textures->east_path);
	game()->textures->west_tex = load(game()->textures->west_path);
}

int	is_valid_path(char *path)
{
	int		fd;
	char	*ext;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close (fd);
	ext = ft_strrchr(path, '.');
	if (!ext || ft_strncmp(ext, ".png", 4))
		return (0);
	return (1);
}

void	finish_get_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	handle_texture(char *line, char **texture, int fd)
{
	char	**split_path;
	char	*trim_path;

	if (*texture != NULL)
	{
		free(line);
		finish_get_line(fd);
		manage_error("Error: duplicate texture!\n");
	}
	split_path = ft_split(line, ' ');
	if (!split_path || !split_path[0] || !split_path[1])
	{
		free_matrix(split_path);
		free(line);
		finish_get_line(fd);
		manage_error("Error: invalid texture path!\n");
	}
	trim_path = ft_strtrim(split_path[1], "\n\t\b\v\r");
	free_matrix(split_path);
	if (!is_valid_path(trim_path))
	{
		free(trim_path);
		free(line);
		finish_get_line(fd);
		manage_error("Error: invalid texture path!\n");
	}
	*texture = ft_strdup(trim_path);
	free(trim_path);
}
