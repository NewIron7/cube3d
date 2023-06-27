/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_easy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:58:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/06/27 11:13:00 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir_step(t_dpoint *dir, t_pvect *player, double *step)
{
	double	angle;

	angle = - PI_6;
	dir->x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	dir->y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	*step = PI_3 / W_WIDTH;
}

void	raycasting(t_pvect player, t_map *map, t_img *img)
{
	t_dpoint	dir;
	int			i;
	double		step;
	t_wall		wall;

	init_dir_step(&dir, &player, &step);
	i = 0;
	while (i < W_WIDTH)
	{
		wall = get_coord_wall(dir, player.pos, map);
		printf("SCREEN dir: (%f, %f)\n", dir.x, dir.y);
		printf("POS: (%d, %d) DIR: (%f, %f)\nORIENT:%d DIST:%f\n", wall.pos.x, wall.pos.y,
				wall.dir.x, wall.dir.y, wall.orient, wall.dist);
		print_col(i, wall.dist, img, wall.orient);
		dir = rotate_vect(&dir, step);
		i++;
	}
}
