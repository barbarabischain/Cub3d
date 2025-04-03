/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:02:30 by babischa          #+#    #+#             */
/*   Updated: 2025/03/25 20:35:13 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	is_map_valid();
// {
// 	verify_
// }

void store_map_in_list(char *line)
{
	char	*copy_line;

	copy_line = ft_strdup(line);
	if (!game()->map_list)
		game()->map_list = ft_lstnew((void*)copy_line);
	else
		ft_lstadd_back(&game()->map_list, ft_lstnew((void*)copy_line));
}

void	get_map(char	*line, int fd)
{
	while (line)
	{
		store_map_in_list(line);
		free(line);
		line = get_next_line(fd);
	}
	list_to_matrix();
	ft_lstclear(&game()->map_list, free);
	// if (!is_map_valid());
	// 	manage_error("Error: Map is not valid\n");
}
