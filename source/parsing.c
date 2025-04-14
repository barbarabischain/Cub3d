/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:39:53 by babischa          #+#    #+#             */
/*   Updated: 2025/04/14 13:29:56 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handle_mapfile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		manage_error("Error: open file.\n");
	get_data_in_file(fd);
	close(fd);
	game()->max_y = count_lines(game()->map);
	game()->max_x = count_columns(game()->map);
	validate_map();
}

void	validate_extension(char *file)
{
	while (*file)
	{
		if (!ft_strncmp(".cub", file, 5))
			return ;
		file++;
	}
	manage_error("error: invalid map extension\n");
}

void	validate(int argc, char **argv)
{
	if (argc != 2)
		manage_error("Error: Invalid argument!\n");
	validate_extension(argv[1]);
	handle_mapfile(argv[1]);
}
