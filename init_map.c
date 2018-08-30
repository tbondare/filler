#include "libfiller.h"

void init_map(char *line, t_map *map)
{
    int i;

    i = 0;
    map->map[map->y] = (char*)malloc(sizeof(char) * map->w);
    while (line[i++])
        map->map[map->y][i] = line[i];
    map->y++;
}

void init_fgr(char *line, t_fgr *fgr)
{
    int i;

    i = 0;
    fgr->fgr[fgr->y] = (char*)malloc(sizeof(char) * fgr->w);
    while (line[i++])
        fgr->fgr[fgr->y][i] = line[i];
    fgr->y++;
}