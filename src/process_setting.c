/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:39 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/21 08:39:50 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_file_path(char *line)
{
	size_t	len;

	while (*line == ' ')
		line++;
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (!len)
	{
		write_error("Texture parameters must have a value");
		return (NULL);
	}
	line = ft_substr(line, 0, len);
	if (!line)
		write_error(NULL);
	return (line);
}

static int	verif_color(char *line)
{
	if (!ft_isdigit(*line))
		return (0);
	while (ft_isdigit(*line))
		line++;
	if (*line++ != ',')
		return (0);
	if (!ft_isdigit(*line))
		return (0);
	while (ft_isdigit(*line))
		line++;
	if (*line++ != ',')
		return (0);
	if (!ft_isdigit(*line))
		return (0);
	while (ft_isdigit(*line))
		line++;
	if (*line != 0 && *line != '\n')
		return (0);
	return (1);
}

static int	process_color(char *line, int type, t_app *app)
{
	unsigned int	color;
	int				inc;

	while (*line == ' ')
		line++;
	if (!verif_color(line))
		return (write_error("Color parameters have incorrect values"));
	inc = ft_atoi(line);
	if (inc < 0 || inc > 255)
		return (write_error("Color parameters have incorrect values"));
	color = inc << 16;
	while (*line != ',')
		line++;
	inc = ft_atoi(++line);
	if (inc < 0 || inc > 255)
		return (write_error("Color parameters have incorrect values"));
	color |= inc << 8;
	while (*line != ',')
		line++;
	inc = ft_atoi(++line);
	if (inc < 0 || inc > 255)
		return (write_error("Color parameters have incorrect values"));
	color |= inc;
	app->colors[type] = color;
	return (1);
}

static void	replace_texture(char **texture, char *new_path)
{
	free(*texture);
	*texture = new_path;
}

int	process_setting(char *line, int type, t_app *app, char *textures[])
{
	char	*path;

	if (type == FLOOR || type == CEILING)
		return (process_color(line + 2, type, app));
	path = read_file_path(line + 3);
	if (!path)
		return (0);
	if (type == LINE_NORTH)
		replace_texture(&textures[NORTH], path);
	else if (type == LINE_SOUTH)
		replace_texture(&textures[SOUTH], path);
	else if (type == LINE_EAST)
		replace_texture(&textures[EAST], path);
	else
		replace_texture(&textures[WEST], path);
	return (1);
}
