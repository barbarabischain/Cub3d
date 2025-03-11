/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:22 by madias-m          #+#    #+#             */
/*   Updated: 2025/03/11 16:36:18 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*load(char *texture_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_path);
	if (!texture)
		ft_printf("deu ruim\n");
	return (texture);
}

void	load_textures(void)
{
	game()->textures->north_tex = load(NO);
	game()->textures->south_tex = load(SO);
	game()->textures->east_tex = load(EA);
	game()->textures->west_tex = load(WE);
}
