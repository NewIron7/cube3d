/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:24:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/24 11:15:19 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	load_xpm_texture(t_app *app, char *filename, int orient)
{
	app->textures[orient].ptr = mlx_xpm_file_to_image(app->mlx_ptr,
			filename, &app->textures[orient].size.x,
			&app->textures[orient].size.y);
	ft_error_malloc(app->textures[orient].ptr, app, NULL);
	app->textures[orient].pxls = mlx_get_data_addr(app->textures[orient].ptr,
			&app->textures[orient].bpp, &app->textures[orient].line_s,
			&app->textures[orient].endian);
}

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

void	load_textures(t_app *app, char *filenames[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (check_extension(filenames[i]))
			load_xpm_texture(app, filenames[i], i);
		else
		{
			printf("ERROR: filename not valid\n");
			ft_close(app);
		}
		i++;
	}
}
