/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:39:53 by babischa          #+#    #+#             */
/*   Updated: 2025/03/10 12:03:34 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	validate_extension(char *file)
{
	while (file)
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
