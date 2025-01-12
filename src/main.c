/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:36:15 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 14:13:38 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_app	app;

	if (argc != 2)
	{
		write_error("Usage : ./cub3d map.cub");
		return (EXIT_FAILURE);
	}
	if (!read_file(argv[1], &app))
		return (EXIT_FAILURE);
	init_raycasting(&app);
	return (EXIT_SUCCESS);
}
