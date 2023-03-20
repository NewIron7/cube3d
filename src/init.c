/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:57:05 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/20 19:01:29 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_struct(t_app *app)
{
	app->mlx_ptr = NULL;
	app->win_ptr = NULL;
	app->map = NULL;
	app->img.ptr = NULL;
	app->img.pxls = NULL;
	app->img.size.x = 0;
	app->img.size.y = 0;
	app->img.bpp = 0;
	app->img.line_s = 0;
	app->img.endian = 0;
}
