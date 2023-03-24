/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:37:44 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/24 09:29:07 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_size_w_dist(double dist)
{
	//return (W_HEIGHT * (A_DIST * dist + B_DIST));
	return ((W_HEIGHT * WALL_SIZE) / dist);
	//return ((W_HEIGHT) / dist);
}

void	print_col_color(int x, double dist, t_img *img, char orient)
{
	int	height;
	int	top;
	int	y;
	int	color;

	color = get_color_by_orient(orient);
	height = get_size_w_dist(dist);
	top = (W_HEIGHT - height) * PLAYER_HEIGHT;
	y = -1;
	while (++y < top)
		put_pixel(img, x, y, C_CEILLING);
	while (height-- && y < img->size.y)
		put_pixel(img, x, y++, color);
	while (y < img->size.y)
		put_pixel(img, x, y++, C_GROUND);
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
