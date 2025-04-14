/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:22 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/14 19:48:08 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cleanup_textures(void)
{
	if (game()->textures->north_tex)
		mlx_delete_texture(game()->textures->north_tex);
	if (game()->textures->south_tex)
		mlx_delete_texture(game()->textures->south_tex);
	if (game()->textures->east_tex)
		mlx_delete_texture(game()->textures->east_tex);
	if (game()->textures->west_tex)
		mlx_delete_texture(game()->textures->west_tex);
	if (game()->textures->north_path)
		free(game()->textures->north_path);
	if (game()->textures->south_path)
		free(game()->textures->south_path);
	if (game()->textures->east_path)
		free(game()->textures->east_path);
	if (game()->textures->west_path)
		free(game()->textures->west_path);
	if (game()->textures)
		free(game()->textures);
}

void	cleanup_memory(void)
{
	if (game()->map)
		free_matrix(game()->map);
	if (game()->map_list)
		ft_lstclear(&game()->map_list, free);
	if (game()->coord)
		free(game()->coord);
	if (game()->textures)
		cleanup_textures();
	if (game())
		free(game());
}

void	manage_error(char *error)
{
	ft_putstr_fd(error, 2);
	cleanup_memory();
	exit(1);
}
