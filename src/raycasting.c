/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:58:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/22 00:41:59 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cube3d.h"

int	get_size_w_dist(double dist)
{
	//return (W_HEIGHT * (A_DIST * dist + B_DIST));
	return ((W_HEIGHT) / dist);
}

int	get_color_by_orient(char orient)
{
	if (orient == NORTH)
		return (C_NORTH);
	if (orient == SOUTH)
		return (C_SOUTH);
	if (orient == EAST)
		return (C_EAST);
	return (C_WEST);
}

void	print_col(int x, double dist, t_img *img, char orient)
{
	int	height;
	int	top;
	int	y;
	int	color;

	color = get_color_by_orient(orient);
	height = get_size_w_dist(dist);
	top = (W_HEIGHT - height) * 0.5;
	y = 0;
	while (y < top)
		y++;
	while (height-- && y < img->size.y)
		put_pixel(img, x, y++, color);
	while (y < img->size.y)
		put_pixel(img, x, y++, C_GROUND);
}

void	init_dir_step(t_dpoint *dir, t_pvect *player, double *step)
{
	double	angle;

	angle = - PI_6;
	dir->x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	dir->y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	*step = PI_3 / W_WIDTH;
}

void	rotate_vect(t_dpoint *vect, double angle)
{
	double	x;

	x = vect->x;
	vect->x = vect->x * cos(angle) - vect->y * sin(angle);
	vect->y = x * sin(angle) + vect->y * cos(angle);
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
		rotate_vect(&dir, step);
		i++;
	}
}
