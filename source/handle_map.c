/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:02:30 by babischa          #+#    #+#             */
/*   Updated: 2025/03/18 17:32:36 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	t_list	*tmp;

	while (line)
	{
		store_map_in_list(line);
		free(line);
		line = get_next_line(fd);
	}
	tmp = game()->map_list;
}
