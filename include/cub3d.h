/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:14:49 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/15 13:53:25 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

#define MAX_Y 24
#define MAX_X 24

#define BLUE 0x99CCFF

#define NO "./textures/north.png"
#define SO "./textures/south.png"
#define WE "./textures/west.png"
#define EA "./textures/east.png"

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	void		*win;
	int			max_x;
	int			max_y;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double 		time;
	double		oldtime;
	mlx_image_t	*image;
	char		key_w;
	char		key_a;
	char		key_s;
	char		key_d;
}	t_game;

// int F[3] = {28,28,28};
// int C[3] = {105,105,105};

t_game	*game(void);
void    key_hook(mlx_key_data_t key_data, void *param);

#endif
