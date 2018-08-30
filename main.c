#include "libfiller.h"
#include <unistd.h>
#include <fcntl.h>


void ft_get_map(t_map *map, char *line, int *fl)
{
    int i;

    if (*fl == 0)
    {
        map->num_pl = ft_atoi(&line[10]);
        (*fl)++;
    }
    else if (*fl == 1)
    {
        i = 8;
        map->h = ft_atoi(&line[i]);
        while (line[i] != ' ')
            i++;
        map->w = ft_atoi(&line[++i]);
        (*fl)++;
    }
    else if (fl == 2)
    {
        map->map = (char **)malloc(sizeof(char*) * map->h);
        map->y = 0;
        (*fl)++;
    }
    if (fl > 2 && fl <= map->h + 2)
        init_map(&line[4], map);
}

void ft_get_fgr(t_fgr *fgr, t_map *map, char *line, int fl)
{
    int i;

    if (fl == map->h + 3)
    {
        i = 6;
        fgr->h = ft_atoi(&line[i]);
        while (line[i] != ' ')
            i++;
        fgr->w = ft_atoi(&line[++i]);
    }
    if (fl == map->h + 4)
    {
        fgr->fgr = (char **)malloc(sizeof(char *) * fgr->h);
        fgr->y = 0;
    }
    if (fl >= map->h + 4 && fl < map->h + fgr->h + 4)
        init_fgr(line, fgr);
}

void printtofile(char *line, int fd)
{
    int i;

    i = 0;
    while (line[i])
    {
        write(fd, &line[i], 1);
        i++;
    }
    write(fd, "\n", 1);
}

int  find_best_crds(t_bst_crn_crd *bcc, t_map *map, t_fgr *fgr)
{
    int x;
    int ym;
    int xm;
    int cnt;

    cnt = 0;
    fgr->y = 0;
    while (fgr->y++ < fgr->h)
    {
        ym = fgr->y + bcc->curr.y;
        x = 0;
        while (x++ < fgr->w)
        {
            xm = x + bcc->curr.x;
            if (fgr->fgr[fgr->y][x] != '*')
                continue;
            else
            {
                if (ym < map->h && ym >= 0 && xm >= 0 && xm < map->w)
                {
                    if (map->map[ym][xm] == map->enemy1 || map->map[ym][xm] == map->enemy2)
                        return (0);
                    if (map->map[ym][xm] == map->player1 || map->map[ym][xm] == map->player2)
                        cnt++;
                    if (cnt > 1)
                        return (0);
                }
                else
                    return (0);
            }
        }
    }
    if (cnt == 0)
        return (0);
    if (cnt == 1)
    {
        int midlx;
        int midly;
        int dist;

        midlx = bcc->curr.x + fgr->w / 2;
        midly = bcc->curr.y + fgr->h / 2;
        dist = (map->enem_crd.x - midlx) * (map->enem_crd.x - midlx) +
                (map->enem_crd.y - midly) * (map->enem_crd.y - midly);
        if (bcc->dist == -1)
        {
            bcc->dist = dist;
            bcc->best.x = bcc->curr.x;
            bcc->best.y = bcc->curr.y;
        }
        else if (dist < bcc->dist)
        {
            bcc->dist = dist;
            bcc->best.x = bcc->curr.x;
            bcc->best.y = bcc->curr.y;
        }
    }
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

t_bst_crn_crd get_coords(t_map *map, t_fgr *fgr)
{
    t_bst_crn_crd bcc;

    bcc.curr.y = 1 - fgr->h;
    bcc.dist = -1;
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
    ft_enem_crd(map);
    while (bcc.curr.y++ < map->h) // get our point on map
    {
        bcc.curr.x = 1 - fgr->w;
        while (bcc.curr.x++ < map->w)
            find_best_crds(&bcc, map, fgr);
    }
    if (bcc.dist != -1)
        return (bcc);
}

void print_answer(t_bst_crn_crd bcc)
{
    char *x;
    char *y;

    x = ft_itoa(bcc.best.x);
    y = ft_itoa(bcc.best.y);
    ft_putstr(x);
    write (1, " ", 1);
    ft_putstr(y);
    write (1, "\n", 1);
    free(x);
    free(y);
}

int main(void)
{
    sleep(10);
    char *line;
    t_map map;
    t_fgr fgr;
    int fd;
    int fl;

    fd = open("notes", O_WRONLY| O_APPEND| O_CREAT, 438);
    line = NULL;
    fl = 0;
    while ((get_next_line(0, &line)) > 0)
    {
        if (fl == 0 || fl == 1 || fl == 2)
            ft_get_map(&map, line, &fl);
        ft_get_fgr(&fgr, &map, line, fl);
        printtofile(line, fd);
        fl++;
        print_answer(get_coords(&map, &fgr));
    }
    return(0);
}