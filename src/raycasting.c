/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:01:02 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/23 22:21:36 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_size_w_dist(double dist)
{
	//return (W_HEIGHT * (A_DIST * dist + B_DIST));
	return ((W_HEIGHT * WALL_SIZE) / dist);
}

t_dpoint	get_vect_orth(t_dpoint a)
{
	t_dpoint	b;

	b.x = -a.y;
	b.y = a.x;
	return (b);
}

t_screen	get_screen_left(void)
{
	t_screen	screen;

	screen.panel = PANEL;
	screen.step = (screen.panel * 2) / W_WIDTH;
	return (screen);
}

t_screen	get_screen_right(void)
{
	t_screen	screen;

	screen.step = (PANEL * 2) / W_WIDTH;
	screen.panel = screen.step;
	return (screen);
}

double	next_dir_screen_left(t_screen *screen, t_pvect *player)
{
	double	angle;

	angle = - PI_2 + atan(1 / screen->panel);
	screen->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	screen->dir.y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	screen->panel -= screen->step;
	return (angle);
}

double	next_dir_screen_right(t_screen *screen, t_pvect *player)
{
	double	angle;

	angle = PI_2 - atan(1 / screen->panel);
	screen->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	screen->dir.y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	screen->panel += screen->step;
	return (angle);
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
	y = -1;
	while (++y < top)
		put_pixel(img, x, y, C_CEILLING);
	while (height-- && y < img->size.y)
		put_pixel(img, x, y++, color);
	while (y < img->size.y)
		put_pixel(img, x, y++, C_GROUND);
}

int	do_raycasting_left(t_pvect *player, t_screen *screen, t_map *map, t_img *img)
{
	int		i;
	t_wall	wall;
	double	angle;

	i = 0;
	while (screen->panel >= 0)
	{
		angle = next_dir_screen_left(screen, player);
		wall = get_coord_wall(screen->dir, player->pos, map);
		//printf("SCREEN dir: (%f, %f)\n", screen->dir.x, screen->dir.y);
		//printf("POS: (%d, %d) DIR: (%f, %f)\nORIENT:%d DIST:%f\n", wall.pos.x, wall.pos.y,
		//		wall.dir.x, wall.dir.y, wall.orient, wall.dist);
		wall.dist *= cos(angle);
		print_col(i, wall.dist, img, wall.orient);
		i++;
	}
	return (i);
}

void	do_raycasting_right(t_pvect *player, t_screen *screen, t_map *map, t_img *img, int i)
{
	t_wall	wall;
	double	angle;

	while (screen->panel <= PANEL && i < W_WIDTH)
	{
		angle = next_dir_screen_right(screen, player);
		wall = get_coord_wall(screen->dir, player->pos, map);
		wall.dist *= cos(-angle);
		print_col(i, wall.dist, img, wall.orient);
		i++;
	}
}

void	raycasting(t_pvect player, t_map *map, t_img *img)
{
	t_screen	screen;
	int			i;

	screen = get_screen_left();
	i = do_raycasting_left(&player, &screen, map, img);
	screen = get_screen_right();
	do_raycasting_right(&player, &screen, map, img, i);
}
