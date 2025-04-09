/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:14:49 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/09 12:07:25 by madias-m         ###   ########.fr       */
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

#define INIT_W 800
#define INIT_H 800

typedef struct s_textures {
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;
} t_textures;

typedef struct s_wall {
	mlx_texture_t	*texture;
	double			x;
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
	char			**map;
	void		    *win;
	int			    max_x;
	int			    max_y;
	char		    key_w;
	char		    key_a;
	char		    key_s;
	char		    key_d;
	char			key_right;
	char			key_left;
	uint32_t		floor;
	uint32_t		ceiling;
	t_list			*map_list;
}	t_game;

t_game	*game(void);
void    key_hook(mlx_key_data_t key_data, void *param);
void    render_loop(void *param);
void	new_movement(void *param);
void    load_textures(void);
void	close_window(void *param);

/*** Parsing ***/
void	validate(int argc, char **argv);
void	manage_error(char *error);
void	get_data_in_file(int fd);
void	handle_texture(char *line, char **texture);
void	handle_color(char *line, uint32_t *color);
void	get_map(char	*line, int fd);
void	set_player_initial_pos(void);
void 	validate_map(void);

/*** Parsing Utils ***/
void	free_matrix(char **matrix);
int		ft_isspace(char c);
int		count_lines(char **matrix);
int 	count_columns(char **matrix);

#endif
