/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:07:08 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/03 11:33:22 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game	*game(void)
{
	static t_game	*game;

	if (!game)
		game = ft_calloc(1, sizeof(t_game));
	return (game);
}

void	init_data(void)
{
	game()->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!(game()->mlx))
	{
 		puts(mlx_strerror(mlx_errno));
 		return ;
 	}
	game()->image = mlx_new_image(game()->mlx, WIDTH, HEIGHT);
	if (!game()->image)
	{
 		puts(mlx_strerror(mlx_errno));
 		return ;
 	}
	if (mlx_image_to_window(game()->mlx, game()->image, 0, 0) == -1)
	{
		mlx_close_window(game()->mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	game()->ceiling = -42;
	game()->floor = -42;
	game()->textures = ft_calloc(1, sizeof(t_textures));
	game()->coord = ft_calloc(1, sizeof(t_coordinates));
	game()->coord->posX = 2;
	game()->coord->posY = 2; //revisar
	game()->coord->dirX = -1.0;
	game()->coord->dirY = 0;
	game()->coord->planeX = 0.0;
	game()->coord->planeY = 0.66;
	game()->map_list = NULL;
}

int main(int argc, char **argv)
{
	init_data();
	validate(argc, argv);
	mlx_loop_hook(game()->mlx, render_loop, NULL);
	mlx_loop_hook(game()->mlx, new_movement, game());
	mlx_key_hook(game()->mlx, key_hook, NULL);
	mlx_close_hook(game()->mlx, close_window, NULL);
	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	return (0);
}
