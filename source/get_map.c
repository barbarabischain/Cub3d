/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:02:30 by babischa          #+#    #+#             */
/*   Updated: 2025/04/14 19:27:10 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

void	print_matrix(void)
{
	int	i;

	i = 0;
	while (game()->map[i])
	{
		printf("%s\n", game()->map[i]);
		i++;
	}
}

void	list_to_matrix(void)
{
	t_list	*tmp;
	char	**matrix;
	int		i;

	tmp = game()->map_list;
	matrix = ft_calloc(ft_lstsize(game()->map_list) + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		matrix[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	game()->map = matrix;
}

void	store_map_in_list(char *line)
{
	char	*copy_line;

	copy_line = ft_strdup(line);
	if (!game()->map_list)
		game()->map_list = ft_lstnew((void *)copy_line);
	else
		ft_lstadd_back(&game()->map_list, ft_lstnew((void *)copy_line));
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
}
