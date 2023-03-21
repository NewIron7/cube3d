/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:01:02 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/21 16:26:26 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_size_w_dist(double dist)
{
	return (W_HEIGHT * (A_DIST * dist + B_DIST));
}

t_dpoint	get_vect_orth(t_dpoint a)
{
	t_dpoint	b;

	b.x = a.y;
	b.y = a.x;
	return (b);
}

t_pvect	get_first_stop(double dist, t_pvect *player)
{
	t_pvect	step;
	t_dpoint	tmp;

	tmp = mult_dpoint(get_vect_orth(player->dir), dist * COS_60);
	step.pos = sum_dpoint(tmp, player->pos);
	step.dir = mult_dpoint(get_vect_orth(player->dir), (-1 * dist * COS_60 * 2) / W_WIDTH);
	return (step);
}

void	print_col(int x, double dist, t_img *img)
{
	int	height;
	int	top;
	int	y;

	height = get_size_w_dist(dist);
	top = (W_HEIGHT - height) * 0.5;
	y = -1;
	while (++y < top)
		put_pixel(img, x, y, C_GREEN);
	while (height--)
		put_pixel(img, x, y++, C_RED);
	while (top--)
		put_pixel(img, x, y++, C_GREEN);
}

t_wall	do_first_ray(t_pvect player, t_map *map, t_img *img)
{
	t_wall	wall;
	double	x;

	x = player.dir.x;
	player.dir.x = player.dir.x * COS_30 - player.dir.y * SIN_30;
	player.dir.y = x * SIN_30 + player.dir.y * COS_30;
	//player.dir.y = player.dir.x * sin(-M_PI/3) + player.dir.y * cos(-M_PI/3);
	//player.dir.x = player.dir.x * cos(-M_PI/3) - player.dir.y * sin(-M_PI/3);
	wall = get_coord_wall(player.dir, player.pos, map);
	print_col(0, wall.dist, img);
	return (wall);	
}

void	do_raycasting(t_pvect *player, t_pvect *step, t_map *map, t_img *img)
{
	int		i;
	t_wall	wall;

	i = 1;
	while (i < W_WIDTH)
	{
		step->pos = sum_dpoint(step->pos, step->dir);
		wall = get_coord_wall(player->dir, step->pos, map);
		print_col(i, wall.dist, img);
		i++;
	}
}

void	raycasting(t_pvect player, t_map *map, t_img *img)
{
	t_pvect step;
	t_wall	wall;

	wall = do_first_ray(player, map, img);
	step = get_first_stop(wall.dist, &player);
	do_raycasting(&player, &step, map, img);
}
