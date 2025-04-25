/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:07:08 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/25 18:05:21 by madias-m         ###   ########.fr       */
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
	game()->ceiling = -42;
	game()->floor = -42;
	(game())->textures = ft_calloc(1, sizeof(t_textures));
	(game())->coord = ft_calloc(1, sizeof(t_coordinates));
	game()->map_list = NULL;
}

void	init_game_window(void)
{
	(game())->mlx = mlx_init(INIT_W, INIT_H, "CUB3D", true);
	if (!(game()->mlx))
	{
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	(game())->image = mlx_new_image(game()->mlx, INIT_W, INIT_H);
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
}

int	main(int argc, char **argv)
{
	init_data();
	validate(argc, argv);
	init_game_window();
	set_player_initial_pos();
	mlx_loop_hook(game()->mlx, render_loop, NULL);
	mlx_loop_hook(game()->mlx, new_movement, game());
	mlx_key_hook(game()->mlx, key_hook, NULL);
	mlx_close_hook(game()->mlx, close_window, NULL);
	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	cleanup_memory();
	return (0);
}
