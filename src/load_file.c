/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/21 01:38:13 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_line_type(char *line)
{
	if (!ft_strncmp("NO ", line, 3))
		return (LINE_NORTH);
	if (!ft_strncmp("SO ", line, 3))
		return (LINE_SOUTH);
	if (!ft_strncmp("WE ", line, 3))
		return (LINE_WEST);
	if (!ft_strncmp("EA ", line, 3))
		return (LINE_EAST);
	if (!ft_strncmp("F ", line, 2))
		return (FLOOR);
	if (!ft_strncmp("C ", line, 2))
		return (CEILING);
	if (*line == '\n' || !*line)
		return (EMPTY);
	return (MAP);
}

static int	process_setting_error(char *line)
{
	free(line);
	return (0);
}

int	load_file(t_app *app, int fd, char *textures[])
{
	char		*line;
	int			type;

	app->colors[FLOOR] = C_GROUND;
	app->colors[CEILING] = C_CEILING;
	line = get_next_line(fd);
	while (line)
	{
		type = get_line_type(line);
		if (type == MAP)
			break ;
		if (type != EMPTY)
		{
			if (!process_setting(line, type, app, textures))
				return (process_setting_error(line));
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (write_error("Empty map"));
	if (!load_map(line, fd, app))
		return (0);
	return (1);
}
