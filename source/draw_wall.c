/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:47:31 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 12:07:09 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static uint32_t	get_texture_color(mlx_texture_t *text, int y, int x)
{
	uint8_t		*pixel;
	int			texture_pos;

	if (x < 0 || x >= (int) text->width || y < 0 || y >= (int) text->height)
		return (0);
	texture_pos = y * text->width + x;
	texture_pos *= text->bytes_per_pixel;
	pixel = &text->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static void	calc_wall_x(t_wall *wall, t_coordinates *coord)
{
	if (coord->side == 1)
		wall->x = coord->posX + coord->perpWallDist * coord->rayDirX;
	else
		wall->x = coord->posY + coord->perpWallDist * coord->rayDirY;
	wall->x -= floor(wall->x);
}

static void	calc_texture_x(t_wall *wall, t_coordinates *coord)
{
	wall->tex_x = (int)(wall->x * wall->texture->width);
	if (coord->side == 0 && coord->rayDirX < 0)
		wall->tex_x = wall->texture->width - wall->tex_x - 1;
	if (coord->side == 1 && coord->rayDirY > 0)
		wall->tex_x = wall->texture->width - wall->tex_x - 1;
}

void	draw_wall(int x, t_coordinates *crd)
{
	t_wall		wall;
	int			y;
	int			tex_y;
	uint32_t	color;

	wall.texture = get_texture();
	calc_wall_x(&wall, crd);
	calc_texture_x(&wall, crd);
	wall.tex_step = 1.0 * wall.texture->height / crd->lineHeight;
	wall.tex_pos = (crd->drawStart - game()->mlx->height / 2);
	wall.tex_pos += crd->lineHeight / 2;
	wall.tex_pos *= wall.tex_step;
	y = crd->drawStart;
	while (y < crd->drawEnd)
	{
		tex_y = (int)wall.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int) wall.texture->height)
			tex_y = wall.texture->height - 1;
		wall.tex_pos += wall.tex_step;
		color = get_texture_color(wall.texture, tex_y, wall.tex_x);
		mlx_put_pixel(game()->image, x, y++, color);
	}
}
