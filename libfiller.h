/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfiller.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:12:33 by tbondare          #+#    #+#             */
/*   Updated: 2018/09/10 19:48:17 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNTITLED1_LIBFILLER_H
# define UNTITLED1_LIBFILLER_H

# define BUFF_SIZE 9

# define IF_MO(a) if (a == -1) return (-1);
# define IF_N(b) if (b == 0) return (0);
# define IF_NU(c) if (c == NULL) return (0);
# define IF_O(d) if (d == 1) return (1);

# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct		s_param
{
	char			**line;
	struct s_lst	*crnt;
	int				res;
}					t_param;

typedef	struct		s_lst
{
	char			*var;
	int				fd;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_crds
{
	int				x;
	int				y;
}					t_crds;

typedef struct		s_map
{
	int				h;
	int				w;
	char			**map;
	int				y;
	int				num_pl;
	char			enemy1;
	char			enemy2;
	char			player1;
	char			player2;
	t_crds			enem_crd;
}					t_map;

typedef struct		s_fgr
{
	int				h;
	int				w;
	char			**fgr;
	int				y;
}					t_fgr;

typedef struct		s_bst_crn_crd
{
	t_crds			curr;
	t_crds			best;
	int				dist;
}					t_bst_crn_crd;

int					get_next_line(const int fd, char **line);

int					main(void);
t_bst_crn_crd		get_coords(t_map *map, t_fgr *fgr);
void				ft_init_pl(t_map *map);
void				ft_free_data(t_map *map, t_fgr *fgr);
void				print_answer(t_bst_crn_crd bcc);

int					ft_get_map(t_map *map);
void				init_map(char *line, t_map *map);
void				ft_get_fgr(t_fgr *fgr);
void				init_fgr(char *line, t_fgr *fgr);

int					find_best_crds(t_bst_crn_crd *bcc, t_map *map, t_fgr *fgr);
int					ft_determ_point(t_bst_crn_crd *bcc,
		t_map *map, t_fgr *fgr, int *cnt);
int					ft_handel_star(int *ym, int *xm, t_map *map, int *cnt);
int					ft_scan_cnt(t_bst_crn_crd *bcc,
		t_map *map, t_fgr *fgr, int cnt);
void				ft_enem_crd(t_map *map);

#endif
