/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:17 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 22:24:39 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	free_textures(char *textures[])
{
	int	i;

	i = 0;
	while (i < 4)
		free(textures[i++]);
	return (0);
}

static int	init_textures(char *textures[])
{
	size_t	len;

	ft_bzero(textures, sizeof(char *) * 4);
	len = ft_strlen(DFL_TXTR_NO);
	textures[NORTH] = ft_calloc(len + 1, sizeof(char));
	if (!textures[NORTH])
		return (free_textures(textures));
	ft_memcpy(textures[NORTH], DFL_TXTR_NO, len);
	len = ft_strlen(DFL_TXTR_SO);
	textures[SOUTH] = ft_calloc(len + 1, sizeof(char));
	if (!textures[SOUTH])
		return (free_textures(textures));
	ft_memcpy(textures[SOUTH], DFL_TXTR_SO, len);
	len = ft_strlen(DFL_TXTR_WE);
	textures[WEST] = ft_calloc(ft_strlen(DFL_TXTR_WE) + 1, sizeof(char));
	if (!textures[WEST])
		return (free_textures(textures));
	ft_memcpy(textures[WEST], DFL_TXTR_WE, len);
	len = ft_strlen(DFL_TXTR_EA);
	textures[EAST] = ft_calloc(ft_strlen(DFL_TXTR_EA) + 1, sizeof(char));
	if (!textures[EAST])
		return (free_textures(textures));
	ft_memcpy(textures[EAST], DFL_TXTR_EA, len);
	return (1);
}

static int	check_extension(char *filename)
{
	int	file_len;
	int	ext_len;

	ext_len = ft_strlen(FILE_EXT);
	file_len = ft_strlen(filename);
	if (file_len < ext_len)
		return (write_error("Map file must follow *.cub format"));
	if (ft_strcmp(filename + (file_len - ext_len), FILE_EXT))
		return (write_error("Map file must follow *.cub format"));
	return (1);
}

static int	start_mlx(t_app *app, char *textures[])
{
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
	{
		free_textures(textures);
		free_map(app->map.map);
		return (write_error("MLX ERROR"));
	}
	if (!load_textures(app, textures))
	{
		free_textures(textures);
		free_map(app->map.map);
		mlx_destroy_display(app->mlx_ptr);
		free(app->mlx_ptr);
		return (0);
	}
	free_textures(textures);
	return (1);
}

int	read_file(char *filename, t_app *app)
{
	int		fd;
	char	*textures[4];

	if (!check_extension(filename))
		return (0);
	ft_bzero(app, sizeof(t_app));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (write_error("Can't open map file"));
	if (!init_textures(textures))
	{
		close(fd);
		return (0);
	}
	if (!load_file(app, fd, textures))
	{
		close(fd);
		free_textures(textures);
		return (0);
	}
	close(fd);
	return (start_mlx(app, textures));
}
