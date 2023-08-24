/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plotline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:54:58 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/24 10:58:20 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	plotline_low(t_point p1, t_point p2, t_point multi, t_img *img)
{
	t_point	d;
	t_point	point;
	int		breakpoint;
	int		i;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	breakpoint = (2 * d.y) - d.x;
	point.y = p1.y;
	point.x = p1.x;
	i = 0;
	while (i < MM_ELEM)
	{
		put_pixel(img, point.x + i * multi.x, point.y, C_MM_DIRECTION);
		if (breakpoint > 0)
		{
			point.y += multi.y;
			breakpoint = breakpoint + (2 * (d.y - d.x));
		}
		else
			breakpoint = breakpoint + 2 * d.y;
		i++;
	}
}

static void	plotline_high(t_point p1, t_point p2, t_point multi, t_img *img)
{
	t_point	d;
	t_point	point;
	int		breakpoint;
	int		i;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	breakpoint = (2 * d.x) - d.y;
	point.x = p1.x;
	point.y = p1.y;
	i = 0;
	while (i < MM_ELEM)
	{
		put_pixel(img, point.x, point.y + i * multi.y, C_MM_DIRECTION);
		if (breakpoint > 0)
		{
			point.x += multi.x;
			breakpoint = breakpoint + (2 * (d.x - d.y));
		}
		else
			breakpoint = breakpoint + 2 * d.x;
		i++;
	}
}

void	ft_plotline(t_point p1, t_point p2, t_point multi, t_img *img)
{
	if (p2.y - p1.y < p2.x - p1.x)
		plotline_low(p1, p2, multi, img);
	else
		plotline_high(p1, p2, multi, img);
}
