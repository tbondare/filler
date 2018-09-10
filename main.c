/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:30:33 by tbondare          #+#    #+#             */
/*   Updated: 2018/09/10 20:02:21 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfiller.h"

void			print_answer(t_bst_crn_crd bcc)
{
	char *x;
	char *y;

	x = ft_itoa(bcc.best.x);
	y = ft_itoa(bcc.best.y);
	ft_putstr(y);
	write(1, " ", 1);
	ft_putstr(x);
	write(1, "\n", 1);
	free(x);
	free(y);
}

void			ft_free_data(t_map *map, t_fgr *fgr)
{
	map->y = 0;
	while (map->y < map->h)
	{
		free(map->map[map->y]);
		map->y++;
	}
	free(map->map);
	fgr->y = 0;
	while (fgr->y < fgr->h)
	{
		free(fgr->fgr[fgr->y]);
		fgr->y++;
	}
	free(fgr->fgr);
}

void			ft_init_pl(t_map *map)
{
	map->player1 = 'O';
	map->enemy1 = 'X';
	map->player2 = 'o';
	map->enemy2 = 'x';
	if (map->num_pl == 2)
	{
		map->player1 = 'X';
		map->enemy1 = 'O';
		map->player2 = 'x';
		map->enemy2 = 'o';
	}
}

t_bst_crn_crd	get_coords(t_map *map, t_fgr *fgr)
{
	t_bst_crn_crd bcc;

	bcc.curr.y = 1 - fgr->h;
	bcc.dist = -1;
	ft_init_pl(map);
	ft_enem_crd(map);
	while (bcc.curr.y < map->h)
	{
		bcc.curr.x = 1 - fgr->w;
		while (bcc.curr.x < map->w)
		{
			find_best_crds(&bcc, map, fgr);
			bcc.curr.x++;
		}
		bcc.curr.y++;
	}
	return (bcc);
}

int				main(void)
{
	char			*line;
	t_map			map;
	t_fgr			fgr;
	t_bst_crn_crd	bcc;

	get_next_line(0, &line);
	map.num_pl = ft_atoi(&line[10]);
	ft_strdel(&line);
	while (1)
	{
		if (ft_get_map(&map) != 1)
			return (0);
		ft_get_fgr(&fgr);
		bcc = get_coords(&map, &fgr);
		if (bcc.dist == -1)
		{
			bcc.best.x = 0;
			bcc.best.y = 0;
			print_answer(bcc);
			return (0);
		}
		print_answer(bcc);
		ft_free_data(&map, &fgr);
	}
}
