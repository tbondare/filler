#ifndef UNTITLED1_LIBFILLER_H
#define UNTITLED1_LIBFILLER_H

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_crds
{
    int x;
    int y;
}t_crds;

typedef struct s_map
{
    int h;
    int w;
    char **map;
    int y;
    int num_pl;
    char enemy1;
    char enemy2;
    char player1;
    char player2;
    t_crds enem_crd;
} t_map;

typedef struct s_fgr
{
    int h;
    int w;
    char **fgr;
    int y;
} t_fgr;

typedef struct s_bst_crn_crd
{
    t_crds curr;
    t_crds best;
    int dist;
}t_bst_crn_crd;

int get_next_line(const int fd, char **line);

void ft_get_map(t_map *map, char *line, int fl);
void ft_get_fgr(t_fgr *fgr, t_map *map, char *line, int fl);
void print_answer(t_bst_crn_crd bcc);

void init_map(char *line, t_map *map);
void init_fgr(char *line, t_fgr *fgr);

#endif //UNTITLED1_LIBFILLER_H
