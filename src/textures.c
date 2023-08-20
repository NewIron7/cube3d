/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:24:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/21 00:27:47 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_xpm_texture(t_app *app, char *filename, int orient)
{
	app->textures[orient].ptr = mlx_xpm_file_to_image(app->mlx_ptr,
			filename, &app->textures[orient].size.x,
			&app->textures[orient].size.y);
	if (!app->textures[orient].ptr)
		return (0);
	app->textures[orient].pxls = mlx_get_data_addr(app->textures[orient].ptr,
			&app->textures[orient].bpp, &app->textures[orient].line_s,
			&app->textures[orient].endian);
	return (1);
}

int	load_textures(t_app *app, char *filenames[])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!load_xpm_texture(app, filenames[i], i))
		{
			while (--i >= 0)
				mlx_destroy_image(app->mlx_ptr, app->textures[i].ptr);
			return (write_error("Texture file failed to load"));
		}
		i++;
	}
	return (1);
}
