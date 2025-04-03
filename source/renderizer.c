/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:36 by madias-m          #+#    #+#             */
/*   Updated: 2025/03/20 16:18:19 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char MAP[MAX_Y][MAX_X] = {
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1'},
	{'1','0','1','0','0','0','0','1','0','1','0','1','0','1','0','1','1','0','0','0','1','1','1','1'},
	{'1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','1'},
	{'1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','1','0','0','0','0','0','0','0','1','1','0','0','0','1','1','1','1'},
	{'1','0','0','0','0','0','0','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','1','1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','0','1','1','0','1','1','0','0','0','0','0','1','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','1','1','0','0','1','0','0','1','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','1','1','0','1','1','0','0','0','0','0','1','1','0','1','1'},
	{'1','0','1','0','1','0','0','0','0','1','1','0','0','0','0','0','1','0','0','0','0','0','0','1'},
	{'1','0','0','1','0','0','0','0','0','1','1','0','1','1','0','0','0','0','0','1','1','0','1','1'},
	{'1','0','1','0','1','0','0','0','0','1','1','0','1','1','0','0','1','0','0','1','0','0','0','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
};

static void	erase_image(void)
{
	int	y;
	int	x;

	mlx_resize_image(game()->image, game()->mlx->width, game()->mlx->height); // nao eh muito pratico, talves seja melhor utilizar um hook especifico
	y = 0;
	while (y < game()->mlx->height / 2)
	{
		x = 0;
		while (x < game()->mlx->width)
			mlx_put_pixel(game()->image, x++, y, 451604479);
		y++;
	}
	while (y < game()->mlx->height)
	{
		x = 0;
		while (x < game()->mlx->width)
			mlx_put_pixel(game()->image, x++, y, 0);
		y++;
	}
}

static void	calc_position_direction(int x, t_coordinates *coord)
{
	coord->rayDirX = coord->dirX + coord->planeX * (2 * x / (double) game()->mlx->width - 1);
	coord->rayDirY = coord->dirY + coord->planeY * (2 * x / (double) game()->mlx->width - 1);
	coord->deltaDistX = sqrt(1 + (coord->rayDirY * coord->rayDirY) / (coord->rayDirX * coord->rayDirX));
	coord->deltaDistY = sqrt(1 + (coord->rayDirX * coord->rayDirX) / (coord->rayDirY * coord->rayDirY));
	coord->mapX = (int) coord->posX;
	coord->mapY = (int) coord->posY;
	if (coord->rayDirX < 0)
	{
		coord->stepX = -1;
		coord->sideDistX = (coord->posX - coord->mapX) * coord->deltaDistX;
	}
	else
	{
		coord->stepX = 1;
		coord->sideDistX = (coord->mapX + 1.0 - coord->posX) * coord->deltaDistX;
	}
	if (coord->rayDirY < 0)
	{
		coord->stepY = -1;
		coord->sideDistY = (coord->posY - coord->mapY) * coord->deltaDistY;
	}
	else
	{
		coord->stepY = 1;
		coord->sideDistY = (coord->mapY + 1.0 - coord->posY) * coord->deltaDistY;
	}
}

static void	process_dda(t_coordinates *coord)
{
	char	hit;

	hit = 0;
	while (hit == 0)
	{
		if (coord->sideDistX < coord->sideDistY)
		{
			coord->sideDistX += coord->deltaDistX;
			coord->mapX += coord->stepX;
			coord->side = 0;
		}
		else
		{
			coord->sideDistY += coord->deltaDistY;
			coord->mapY += coord->stepY;
			coord->side = 1;
		}
		if (MAP[coord->mapX][coord->mapY] == '1')
			hit = 1;
	}
}

static void	calc_perpendicular_ray(t_coordinates *coord)
{	
	if (coord->side == 0)
		coord->perpWallDist = (coord->sideDistX - coord->deltaDistX);
	else
		coord->perpWallDist = (coord->sideDistY - coord->deltaDistY);
	coord->lineHeight = (int)(game()->mlx->height / coord->perpWallDist);
	coord->drawStart = -coord->lineHeight / 2 + game()->mlx->height / 2;
	coord->drawEnd = coord->lineHeight / 2 + game()->mlx->height / 2;
	if (coord->drawStart < 0)
		coord->drawStart = 0;
	if (coord->drawEnd > game()->mlx->height)
		coord->drawEnd = game()->mlx->height - 1;
}

static mlx_texture_t	*get_texture(void)
{
	if (game()->coord->side == 1)
	{
		if (game()->coord->stepY < 0)
			return (game()->textures->north_tex);
		else
			return (game()->textures->south_tex);
	}
	else
	{
		if (game()->coord->stepX < 0)
			return (game()->textures->west_tex);
		else
			return (game()->textures->east_tex);
	}
	return (0);
}

static uint32_t	get_texture_color(mlx_texture_t *texture, int y, int x)
{
	uint8_t		*pixel;
	int			texture_pos;

	if (x < 0 || x >= (int) texture->width || y < 0 || y >= (int) texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static void	draw_wall(int x, t_coordinates *coord)
{
	t_wall		wall;
	int			y;
	int			tex_y;
	uint32_t	color;

	wall.texture = get_texture();
	if (coord->side == 1)
		wall.x = coord->posX + coord->perpWallDist * coord->rayDirX;
	else
		wall.x = coord->posY + coord->perpWallDist * coord->rayDirY;
	wall.x -= floor(wall.x);
	wall.texX = (int)(wall.x * wall.texture->width);
	if (coord->side == 1 && coord->rayDirY > 0)
		wall.texX = wall.texture->width - wall.texX - 1;
	else if (coord->side == 0 && coord->rayDirX < 0)
		wall.texX = wall.texture->width - wall.texX - 1;
	wall.texStep = 1.0 * wall.texture->height / coord->lineHeight;
	wall.texPos = (coord->drawStart - game()->mlx->height / 2 + coord->lineHeight / 2) * wall.texStep;
	y = coord->drawStart;
	while (y < coord->drawEnd)
	{
		tex_y = (int)wall.texPos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int) wall.texture->height)
			tex_y = wall.texture->height - 1;
		wall.texPos += wall.texStep;
		color = get_texture_color(wall.texture, tex_y, wall.texX);
		mlx_put_pixel(game()->image, x, y++, color);
	}
}

void	render_loop(void *param)
{
	int	x;

	(void)param;
	erase_image();
	x = 0;
	while (x < game()->mlx->width)
	{
		calc_position_direction(x, game()->coord);
		process_dda(game()->coord);
		calc_perpendicular_ray(game()->coord);
		draw_wall(x, game()->coord);
		x++;
	}
}
