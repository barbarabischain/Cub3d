/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:50:26 by babischa          #+#    #+#             */
/*   Updated: 2025/03/14 15:19:07 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void cleanup_game(void)
{
	if (!game())
		return;
}

void cleanup_memory(void)
{
	cleanup_game();
}

void	manage_error(char *error)
{
	ft_putstr_fd(error, 2);
	cleanup_memory();
	exit(1);
}
