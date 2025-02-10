/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:07:08 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/10 15:54:05 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game *game(void)
{
	static	t_game *game;

	if (!game)
		game = ft_calloc(1, sizeof(t_game));
	return (game);
}

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

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
	if (!(game()->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
	{
 		puts(mlx_strerror(mlx_errno));
 		return ;
 	}
	if (!(game()->image = mlx_new_image(game()->mlx, WIDTH, HEIGHT)))
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

 	mlx_loop_hook(game()->mlx, put_background, game()->mlx);
 	mlx_loop(game()->mlx);
 	mlx_terminate(game()->mlx);
 	return ;
}

int main(void)
{
	init_data();
	return (0);
}
