/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:14:49 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/21 12:05:43 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>

#define WIDTH 512
#define HEIGHT 512

#define MAX_Y 24
#define MAX_X 24

#define BLUE 0x99CCFF

#define NO "./textures/north.png"
#define SO "./textures/south.png"
#define WE "./textures/west.png"
#define EA "./textures/east.png"

typedef struct s_textures {
  mlx_texture_t  *north_tex;
  mlx_texture_t  *south_tex;
  mlx_texture_t  *east_tex;
  mlx_texture_t  *west_tex;
} t_textures;

typedef struct s_wall {
	mlx_texture_t	*texture;
	int				x;
	int				texX;
	double			texStep;
	double			texPos;
}	t_wall;

typedef struct s_coordinates {
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	char		side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
}	t_coordinates;

typedef struct s_game
{
	mlx_t		    *mlx;
	mlx_image_t		*image;
	t_coordinates	*coord;
  	t_textures  	*textures;
	int			    map[24][24];
	void		    *win;
	int			    max_x;
	int			    max_y;
	char		    key_w;
	char		    key_a;
	char		    key_s;
	char		    key_d;
}	t_game;

// int F[3] = {28,28,28};
// int C[3] = {105,105,105};



t_game	*game(void);
void    key_hook(mlx_key_data_t key_data, void *param);
void    render_loop(void *param);
void	movement(void *param);
void    load_textures(void);

#endif
