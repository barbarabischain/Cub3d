/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:22 by madias-m          #+#    #+#             */
/*   Updated: 2025/03/17 11:43:08 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*load(char *texture_path)
{
	mlx_texture_t *texture;

	texture = mlx_load_png(texture_path);
	if (!texture)
		ft_printf("deu ruim\n");
	return (texture);
}

void	load_textures(void)
{
	game()->textures->north_tex = load(game()->textures->north_path);
	game()->textures->south_tex = load(game()->textures->south_path);
	game()->textures->east_tex = load(game()->textures->east_path);
	game()->textures->west_tex = load(game()->textures->west_path);
}
