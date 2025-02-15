/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:07:08 by madias-m          #+#    #+#             */
/*   Updated: 2025/02/15 14:46:09 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <sys/time.h>
#include <math.h>

int MAP[MAX_Y][MAX_X] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_game	*game(void)
{
	static t_game	*game;

	if (!game)
		game = ft_calloc(1, sizeof(t_game));
	return (game);
}

void draw_horizontal_line(int y, int drawStart, int drawEnd, uint32_t color)
{
	while (drawStart <= drawEnd)
		mlx_put_pixel(game()->image, y, drawStart++, color);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	render_hook(void *param)
{
	int 	y;
	double 	cameraY;
	double 	rayDirY;
	double 	rayDirX;
	int 	mapY;
	int 	mapX;
	double	sideDistY;
	double	sideDistX;
	double	deltaDistY;
	double	deltaDistX;
	double	perpWallDist;
	int		stepY;
	int		stepX;
	int		hit;
	int		side;
	int 	lineHeight;
	int 	drawStart;
	int		drawEnd;
	uint32_t	color;
	double	frameTime;
	double	moveSpeed;
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;
	
	y = 0;
	(void) param;
	while (y < WIDTH)
	{
		cameraY = 2 * y / (double) WIDTH - 1;
		rayDirY = game()->dirY + game()->planeY * cameraY;
		rayDirX = game()->dirX + game()->planeX * cameraY;
		
		mapY = (int) game()->posY;
		mapX = (int) game()->posX;
		
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);

		hit = 0;
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game()->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game()->posY) * deltaDistY;
		}
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game()->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game()->posX) * deltaDistX;
		}
		while (hit == 0)
		{
			if (sideDistY < sideDistX)
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 0;
			}
			else
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 1;
			}
			if (MAP[mapY][mapX] > 0)
				hit = 1; 
		}
		
		if (side == 0)
			perpWallDist = sideDistY - deltaDistY;
		else
			perpWallDist = sideDistX - deltaDistX;
		
		lineHeight = (int) (HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) 
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		color = ft_pixel(
			0xFF0000, // R
			0x0000FF, // G
			0x00FF00, // B
			0xFF  // A
		);
		if (side == 1)
			color = color / 2;
		draw_horizontal_line(y++, drawStart, drawEnd, color);
	}
	
	frameTime = game()->mlx->delta_time;
	moveSpeed = frameTime * 5.0;
	rotSpeed = frameTime * 3.0;

	if (game()->key_w)
	{
		if (MAP[(int) (game()->posY + game()->dirY * moveSpeed)][(int)(game()->posX)] == 0)
			game()->posY += game()->dirY * moveSpeed;
		if (MAP[(int)(game()->posY)][(int) (game()->posX + game()->dirX * moveSpeed)] == 0)
			game()->posX += game()->dirX * moveSpeed;
	}
	if (game()->key_s)
	{
		if (MAP[(int) (game()->posY + game()->dirY * moveSpeed)][(int)(game()->posX)] == 0)
			game()->posY -= game()->dirY * moveSpeed;
		if (MAP[(int)(game()->posY)][(int) (game()->posX + game()->dirX * moveSpeed)] == 0)
			game()->posX -= game()->dirX * moveSpeed;
	}
	if (game()->key_a)
	{
		oldDirX = game()->dirX;
		game()->dirX = game()->dirX * cos(-rotSpeed) - game()->dirY * sin(-rotSpeed);
		game()->dirY = oldDirX * sin(-rotSpeed) + game()->dirY * cos(-rotSpeed);
		oldPlaneX = game()->planeX;
		game()->planeX = game()->planeX * cos(-rotSpeed) - game()->planeY * sin(-rotSpeed);
		game()->planeY = oldPlaneX * sin(-rotSpeed) + game()->planeY * cos(-rotSpeed);
	}
	if (game()->key_d)
	{
		oldDirX = game()->dirX;
		game()->dirX = game()->dirX * cos(rotSpeed) - game()->dirY * sin(rotSpeed);
		game()->dirY = oldDirX * sin(rotSpeed) + game()->dirY * cos(rotSpeed);
		oldPlaneX = game()->planeX;
		game()->planeX = game()->planeX * cos(rotSpeed) - game()->planeY * sin(rotSpeed);
		game()->planeY = oldPlaneX * sin(rotSpeed) + game()->planeY * cos(rotSpeed);
	}
	
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
	game()->posY = 22;
	game()->posX = 12;
	game()->dirY = -1;
	game()->dirX = 0;
	game()->planeY = 0;
	game()->planeX = 0.66;
}

int main(void)
{
	init_data();
	mlx_loop_hook(game()->mlx, render_hook, NULL);
	mlx_key_hook(game()->mlx, key_hook, NULL);
	mlx_loop(game()->mlx);
	mlx_terminate(game()->mlx);
	return (0);
}
