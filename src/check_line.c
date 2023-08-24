/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:24:45 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/24 10:50:13 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_up(char *line, char *prev, int i, int prev_len)
{
	if (ft_strchr(" 1", line[i]))
		return (1);
	if (i == 0 || !line[i + 1] || line[i + 1] == '\n')
		return (write_error("Map isn't closed"));
	if (i >= prev_len || !ft_strchr("01NSEW", prev[i]))
		return (write_error("Map isn't closed"));
	return (1);
}

static int	check_down(char *line, char *next, int next_len)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr(" 1", line[i]))
		{
			if (i >= next_len || !ft_strchr("01NSEW", next[i]))
				return (write_error("Map isn't closed"));
		}
		i++;
	}
	return (1);
}

static int	init_player(t_pvect *player, char *line, int x, int y)
{
	if (player->pos.x)
		return (write_error("Map has multiple starting positions"));
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	if (ft_strchr("NS", line[x]))
	{
		player->dir.x = 0;
		player->dir.y = 1;
		if (line[x] == 'N')
			player->dir.y = -1;
	}
	else
	{
		player->dir.y = 0;
		player->dir.x = 1;
		if (line[x] == 'W')
			player->dir.x = -1;
	}
	line[x] = CHAR_BLANK;
	return (1);
}

int	check_line(char *line, char *prev, t_app *app)
{
	int	i;
	int	prev_len;

	if (!line)
		return (check_down(prev, NULL, 0));
	prev_len = 0;
	if (prev)
		prev_len = ft_strlen(prev);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (write_error("Invalid character in map"));
		if (!check_up(line, prev, i, prev_len))
			return (0);
		if (ft_strchr("NSEW", line[i])
			&& !init_player(&app->player, line, i, app->map.size.y))
			return (0);
		i++;
	}
	if (i > app->map.size.x)
		app->map.size.x = i;
	return (check_down(prev, line, i));
}
