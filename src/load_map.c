/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:25:37 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/31 15:05:39 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_map_error(t_map *map)
{
	free_map(map->map);
	map->map = NULL;
	return (0);
}

static int	map_realloc(char ***map, int height)
{
	char	**new_map;

	new_map = ft_calloc(height + REALLOC_BUFF_SIZE + 1, sizeof(char *));
	if (!new_map)
	{
		free_map(*map);
		return (write_error("Out of memory"));
	}
	while (height--)
		new_map[height] = (*map)[height];
	free(*map);
	*map = new_map;
	return (1);
}

static char	*remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		i++;
	}
	return (line);
}

static int	square_map(t_map *map)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (i < map->size.y)
	{
		new_line = malloc(sizeof(char) * (map->size.x + 1));
		if (!new_line)
			return (load_map_error(map));
		j = 0;
		while (map->map[i][j])
		{
			new_line[j] = map->map[i][j];
			j++;
		}
		while (j < map->size.x)
			new_line[j++] = ' ';
		new_line[j] = '\0';
		free(map->map[i]);
		map->map[i] = new_line;
		i++;
	}
	return (1);
}

int	load_map(char *line, int fd, t_app *app)
{
	char	*prev;

	prev = NULL;
	while (line)
	{
		if (!check_line(line, prev, app))
		{
			free(line);
			return (load_map_error(&app->map));
		}
		if (!(app->map.size.y % REALLOC_BUFF_SIZE)
			&& !map_realloc(&app->map.map, app->map.size.y))
			return (load_map_error(&app->map));
		app->map.map[app->map.size.y++] = remove_newline(line);
		prev = line;
		line = get_next_line(fd);
	}
	if (!check_line(NULL, prev, app))
		return (load_map_error(&app->map));
	if (!app->player.pos.x)
	{
		write_error("Map missing a starting position");
		return (load_map_error(&app->map));
	}
	return (square_map(&app->map));
}
