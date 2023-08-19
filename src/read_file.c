/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:17 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/06/27 16:24:44 by ddelhalt         ###   ########.fr       */
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

static void	fill_texture(char *texture, char *filename)
{
	while (*filename)
		*texture++ = *filename++;
}

static int	init_textures(char *textures[])
{
	ft_bzero(textures, sizeof(char *) * 4);
	textures[NORTH] = ft_calloc(ft_strlen(DFL_TXTR_NO) + 1, sizeof(char));
	if (!textures[NORTH])
		return (free_textures(textures));
	textures[SOUTH] = ft_calloc(ft_strlen(DFL_TXTR_SO) + 1, sizeof(char));
	if (!textures[SOUTH])
		return (free_textures(textures));
	textures[WEST] = ft_calloc(ft_strlen(DFL_TXTR_WE) + 1, sizeof(char));
	if (!textures[WEST])
		return (free_textures(textures));
	textures[EAST] = ft_calloc(ft_strlen(DFL_TXTR_EA) + 1, sizeof(char));
	if (!textures[EAST])
		return (free_textures(textures));
	fill_texture(textures[NORTH], DFL_TXTR_NO);
	fill_texture(textures[SOUTH], DFL_TXTR_SO);
	fill_texture(textures[WEST], DFL_TXTR_WE);
	fill_texture(textures[EAST], DFL_TXTR_EA);
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

t_app	*read_file(char *filename)
{
	int		fd;
	t_app	*app;
	char	*textures[4];

	if (!check_extension(filename))
		return (NULL);
	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(app);
		return (NULL);
	}
	if (!init_textures(textures))
	{
		close(fd);
		free(app);
		return (NULL);
	}
	if (!load_file(app, fd, textures))
	{
		free(app);
		close(fd);
		free_textures(textures);
		return (NULL);
	}
	close(fd);
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		write_error("MLX ERROR");
	load_textures(app, textures);
	free_textures(textures);
	return (app);
}
