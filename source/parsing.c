/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:39:53 by babischa          #+#    #+#             */
/*   Updated: 2025/03/10 12:31:04 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_extension(char *file)
{

	while (*file)
	{
		if (!ft_strncmp(".cub", file, 5))
			return;
		file++;
	}
	printf("error: invalid map extension\n");
	//funcao de saida
	exit(2);
}

void	validate(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: Invalid argument!\n");
		//funcao de saida
		exit(2);
	}
	validate_extension(argv[1]);

}
