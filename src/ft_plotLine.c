/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plotLine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:54:58 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/23 18:56:27 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	plotLineLow(t_point p1, t_point p2, t_point multi, t_img *img)
{
	t_point	d;
	t_point	point;
	int		D;
	int		i;

    d.x = p2.x - p1.x;
    d.y = p2.y - p1.y;
    D = (2 * d.y) - d.x;
    point.y = p1.y;
	i = 0;
	while (i < MM_ELEM)
	{
		put_pixel(img, point.x + i * multi.x, point.y, C_MM_DIRECTION);
        if (D > 0)
		{
            point.y += multi.y;
            D = D + (2 * (d.y - d.x));
		}
        else
            D = D + 2 * d.y;
		i++;
	}
}

static void	plotLineHigh(t_point p1, t_point p2, t_point multi, t_img *img)
{
	t_point	d;
	t_point	point;
	int		D;
	int		i;

    d.x = p2.x - p1.x;
    d.y = p2.y - p1.y;
    D = (2 * d.x) - d.y;
    point.x = p1.x;
	i = 0;
	while (i < MM_ELEM)
	{
		printf("drawing point at %d:%d\n", point.x, point.y + i * multi.y);
		put_pixel(img, point.x, point.y + i * multi.y, C_MM_DIRECTION);
        if (D > 0)
		{
            point.x += multi.x;
            D = D + (2 * (d.x - d.y));
		}
        else
            D = D + 2 * d.x;
		i++;
	}
}

void	ft_plotLine(t_point p1, t_point p2, t_point multi, t_img *img)
{
    if (p2.y - p1.y < p2.x - p1.x)
            plotLineLow(p1, p2, multi, img);
    else
            plotLineHigh(p1, p2, multi, img);
}
