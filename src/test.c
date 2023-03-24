/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:22:46 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/24 11:06:46 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cube3d.h"

static void	cpy_map(char tmp[10][24], int w, int h, char ***map)
{
	int	x;
	int	y;

	*map = malloc(sizeof(char *) * h);
	y = 0;
	while (y < h)
	{
		x = 0;
		(*map)[y] = malloc(w);
		while (x < w)
		{
			(*map)[y][x] = tmp[y][x];
			x++;
		}
		y++;
	}
}

void	init_map(t_map *map)
{
	char	tmp[10][24] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	cpy_map(tmp, 24, 10, &map->map);
	map->size.x = 24;
	map->size.y = 10;
}

void	init_player(t_pvect	*player)
{
	player->dir.x = 0;
	player->dir.y = 1;
	player->pos.x = 2.5;
	player->pos.y = 2.5;
}

void	init_textures(t_app *app)
{
	char	*filenames[4];

	filenames[0] = "textures/brick.xpm";
	filenames[1] = "textures/metal.xpm";
	filenames[2] = "textures/wood.xpm";
	filenames[3] = "textures/stone.xpm";
	load_textures(app, filenames);
}

void	init_raycasting(t_app *app)
{
	init_map(&app->map);
	init_player(&app->player);
	init_textures(app);
	//raycasting(app);
}
