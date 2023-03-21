/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:22:46 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/22 00:41:35 by hboissel         ###   ########.fr       */
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

void	test_get_coord_wall(t_img *img)
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
	t_map	map;
	t_dpoint	dir;
	t_dpoint	pos;
	//t_wall		wall;
	t_pvect		player;

	cpy_map(tmp, 24, 10, &map.map);
	map.size.x = 24;
	map.size.y = 10;
	dir.x = cos((M_PI * 2)/3);
	dir.y = sin((M_PI*2)/3);
	pos.x = 20.5;
	pos.y = 3.5;
	player.dir = dir;
	player.pos = pos;
	raycasting(player, &map, img);
	//wall = get_coord_wall(dir, pos, &map);
	//printf("POS: (%d, %d) DIR: (%f, %f)\nORIENT:%d DIST:%f\n", wall.pos.x, wall.pos.y,
	//		wall.dir.x, wall.dir.y, wall.orient, wall.dist);
}
