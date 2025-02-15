/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:03:09 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/15 13:55:51 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	key_pressed_handle(mlx_key_data_t key_data)
{
	ft_printf("pressed\n");
	if (key_data.key == MLX_KEY_W)
		game()->key_w = 1;
	else if (key_data.key == MLX_KEY_S)
		game()->key_s = 1;
	else if (key_data.key == MLX_KEY_A)
		game()->key_a = 1;
	else if (key_data.key == MLX_KEY_D)
		game()->key_d = 1;
}

static void key_release_handle(mlx_key_data_t key_data)
{
	ft_printf("released\n");
	if (key_data.key == MLX_KEY_W)
		game()->key_w = 0;
	else if (key_data.key == MLX_KEY_S)
		game()->key_s = 0;
	else if (key_data.key == MLX_KEY_A)
		game()->key_a = 0;
	else if (key_data.key == MLX_KEY_D)
		game()->key_d = 0;
}

void	key_hook(mlx_key_data_t key_data, void *param)
{
	(void)param;
	// if (pressed ESC)

	if (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT)
		key_pressed_handle(key_data);
	else if (key_data.action == MLX_RELEASE)
		key_release_handle(key_data);
}