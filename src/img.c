/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:21:39 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/20 19:24:11 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_color_pixel(t_img *img, int x, int y)
{
	int	pos;
	unsigned int	*color_ptr;

	pos = 0;
	if (x < W_WIDTH && y < W_HEIGHT && x > 0 && y > 0)
	{
		pos = (x * img->bpp / 8) + (y * img->line_s);
		color_ptr = (unsigned int *)(img->pxls + pos);
	}
	return (*color_ptr);
}

void	put_pixel(t_img *img, int x, int y, unsigned int color)
{
	int	pos;

	pos = 0;
	if (x < W_WIDTH && y < W_HEIGHT && x > 0 && y > 0)
	{
		pos = (x * img->bpp / 8) + (y * img->line_s);
		img->pxls[pos] = color;
		img->pxls[++pos] = color >> 8;
		img->pxls[++pos] = color >> 16;
	}
}

void	new_img(t_app *app, void *mlx, int width, int height)
{
	app->img.size.x = width;
	app->img.size.y = height;
	app->img.ptr = mlx_new_image(mlx, app->img.size.x, app->img.size.y);
	ft_error_malloc(app->img.ptr, app, NULL);
	app->img.pxls = mlx_get_data_addr(app->img.ptr, &app->img.bpp,
			&app->img.line_s, &app->img.endian);
}
