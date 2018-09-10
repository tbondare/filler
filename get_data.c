/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 17:06:29 by tbondare          #+#    #+#             */
/*   Updated: 2018/09/10 19:43:42 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfiller.h"

void	init_map(char *line, t_map *map)
{
	int i;

	i = 0;
	map->map[map->y] = (char*)malloc(sizeof(char) * map->w);
	while (line[i])
	{
		map->map[map->y][i] = line[i];
		i++;
	}
	map->y++;
}

void	init_fgr(char *line, t_fgr *fgr)
{
	int i;

	i = 0;
	fgr->fgr[fgr->y] = (char*)malloc(sizeof(char) * fgr->w);
	while (line[i])
	{
		fgr->fgr[fgr->y][i] = line[i];
		i++;
	}
	fgr->y++;
}

int		ft_get_map(t_map *map)
{
	int		i;
	char	*line;

	i = get_next_line(0, &line);
	if (i != 1)
		return (0);
	i = 8;
	map->h = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	map->w = ft_atoi(&line[++i]);
	ft_strdel(&line);
	map->map = (char **)malloc(sizeof(char*) * map->h);
	map->y = 0;
	get_next_line(0, &line);
	ft_strdel(&line);
	while (map->y < map->h)
	{
		get_next_line(0, &line);
		init_map(&line[4], map);
		ft_strdel(&line);
	}
	return (1);
}

void	ft_get_fgr(t_fgr *fgr)
{
	int		i;
	char	*line;

	i = 6;
	get_next_line(0, &line);
	fgr->h = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	fgr->w = ft_atoi(&line[++i]);
	fgr->fgr = (char **)malloc(sizeof(char *) * fgr->h);
	fgr->y = 0;
	ft_strdel(&line);
	while (fgr->y < fgr->h)
	{
		get_next_line(0, &line);
		init_fgr(line, fgr);
		ft_strdel(&line);
	}
}
