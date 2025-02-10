/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:07:08 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/10 17:43:20 by babischa         ###   ########.fr       */
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

void	put_background(void *param)
{
	int	x;
	int	y;

	y = 0;
	while (y < game()->max_y)
	{
		x = 0;
		while (x < game()->max_x)
		{
			mlx_put_pixel(game()->image, x, y, BLUE);
			x++;
		}
		y++;
	}
	(void)param;
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
	game()->max_x = WIDTH;
	game()->max_y = HEIGHT / 2;
}

void	finish_data()
{
	mlx_loop_hook(game()->mlx, put_background, game()->mlx);
 	mlx_loop(game()->mlx);
 	mlx_terminate(game()->mlx);
}

int main(void)
{
	init_data();
	finish_data();
	return (0);
}
