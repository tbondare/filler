/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 17:11:48 by tbondare          #+#    #+#             */
/*   Updated: 2018/09/08 20:48:27 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfiller.h"

int ft_scan_cnt(t_bst_crn_crd *bcc, t_map *map, t_fgr *fgr, int cnt)
{
	int midlx;
	int midly;
	int dist;
	
	if (cnt == 0)
		return (0);
	if (cnt == 1)
	{
		midlx = bcc->curr.x + fgr->w / 2;
		midly = bcc->curr.y + fgr->h / 2;
		dist = (map->enem_crd.x - midlx) * (map->enem_crd.x - midlx) +
			(map->enem_crd.y - midly) * (map->enem_crd.y - midly);
		if (bcc->dist == -1 || dist < bcc->dist)
		{
			bcc->dist = dist;
			bcc->best.x = bcc->curr.x;
			bcc->best.y = bcc->curr.y;
		}
	}
	return (1);
}

int ft_handel_star(int *ym, int *xm, t_map *map, int *cnt)
{
	if (*ym < map->h && *ym >= 0 && *xm >= 0 && *xm < map->w)
	{
		if (map->map[(*ym)][(*xm)] == map->enemy1 ||
				map->map[(*ym)][(*xm)] == map->enemy2)
			return (0);
		if (map->map[(*ym)][(*xm)] == map->player1 ||
				map->map[(*ym)][(*xm)] == map->player2)
			(*cnt)++;
		if (*cnt > 1)
			return (0);
	}
	else
		return (0);
	return (1);
}

int ft_determ_point(t_bst_crn_crd *bcc, t_map *map, t_fgr *fgr, int *cnt)
{
	int x;
    int ym;
    int xm;

	ym = fgr->y + bcc->curr.y;
    x = 0;
    while (x < fgr->w)
    {
		xm = x + bcc->curr.x;
        if (fgr->fgr[fgr->y][x] != '*')
        {
			x++;
            continue;
         }
		else
			if (ft_handel_star(&ym, &xm, map, cnt) == 0)
				return (0);
		x++;
	}
	fgr->y++;
	return (1);
}

int  find_best_crds(t_bst_crn_crd *bcc, t_map *map, t_fgr *fgr)
{
    int cnt;

    cnt = 0;
    fgr->y = 0;
    while (fgr->y < fgr->h)
		if (ft_determ_point(bcc, map, fgr, &cnt) == 0)
			return (0);
	if (ft_scan_cnt(bcc, map, fgr, cnt) == 0)
		return (0);
    return (1);
}

void ft_enem_crd(t_map *map)
{
    int i;
    int j;

    j = 0;
    while (j++ < map->h)
    {
        i = 0;
        while (i++ < map->w)
          if (map->map[j][i] == map->enemy1)
          {
              map->enem_crd.y = j;
              map->enem_crd.x = i;
              return ;
          }
    }
}
