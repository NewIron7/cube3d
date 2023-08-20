/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:24:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/20 14:10:57 by ddelhalt         ###   ########.fr       */
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

/*
static char	check_extension(char *filename)
{
	int		i;
	char	*xpm;

	xpm = ".xpm";
	i = ft_strlen(filename) - 4;
	if (ft_strncmp(xpm, &filename[i], 5) == 0)
		return (1);
	return (0);
}
*/

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
		/*
		if (check_extension(filenames[i]))
			load_xpm_texture(app, filenames[i], i);
		else
		{
			printf("ERROR: filename not valid\n");
			ft_close(app);
		}
		*/
		i++;
	}
	return (1);
}
