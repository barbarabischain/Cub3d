/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:31:12 by babischa          #+#    #+#             */
/*   Updated: 2025/04/03 11:10:38 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int	count_lines(int fd)
{
	int		count;
	char	*temp;

	count = 0;

	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
		count++;
	}
	close (fd);
	return (count);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char*)list->content);
		list = list->next;
	}
}

void print_matrix(void)
{
	int i;

	i = 0;
	while (game()->map[i])
	{
		printf("%s\n", game()->map[i]);
		i++;
	}
}

void list_to_matrix(void)
{
	t_list	*tmp;
	char	**matrix;
	int		i;

	tmp = game()->map_list;
	matrix = ft_calloc(ft_lstsize(game()->map_list) + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		matrix[i] = ft_strdup((char*)tmp->content);
		tmp = tmp->next;
		i++;
	}
	game()->map = matrix;
}
