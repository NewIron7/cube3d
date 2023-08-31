/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_textured.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:37:44 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/31 14:55:38 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_size_w_dist(double dist)
{
	return ((W_HEIGHT * WALL_SIZE) / dist);
}

static t_point	get_pos_pxl_texture(t_img *texture, t_wall *wall, int y)
{
	t_point	pos;
	double	coef;

	pos.y = y * ((double) texture->size.y / get_size_w_dist(wall->dist));
	if (wall->orient == NORTH || wall->orient == SOUTH)
		coef = (wall->dir.x - (int)wall->dir.x);
	else
		coef = (wall->dir.y - (int)wall->dir.y);
	pos.x = texture->size.x * coef;
	return (pos);
}

static unsigned int	get_color_pxl_texture(t_img *texture, t_wall *wall, int y)
{
	t_point			pos;
	unsigned int	color;

	pos = get_pos_pxl_texture(texture, wall, y);
	color = get_color_pixel(texture, pos.x, pos.y);
	return (color);
}

void	print_wall_textured(int x, t_wall *wall, t_app *app)
{
	int	height;
	int	color;
	int	y;
	int	top;

	height = get_size_w_dist(wall->dist);
	top = (W_HEIGHT - height) * PLAYER_HEIGHT;
	y = -1;
	while (++y < top && app->img.size.y)
		put_pixel(&app->img, x, y, app->colors[CEILING]);
	while (height-- && y < app->img.size.y)
	{
		color = get_color_pxl_texture(
				&app->textures[(int)wall->orient], wall, y - top);
		put_pixel(&app->img, x, y, color);
		y++;
	}
	while (y < app->img.size.y)
		put_pixel(&app->img, x, y++, app->colors[FLOOR]);
}
