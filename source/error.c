/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madias-m <madias-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:22 by madias-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:08:47 by madias-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cleanup_game(void)
{
	if (!game())
		return ;
}

void	cleanup_memory(void)
{
	cleanup_game();
}

void	manage_error(char *error)
{
	ft_putstr_fd(error, 2);
	cleanup_memory();
	exit(1);
}
