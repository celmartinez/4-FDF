/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:22:20 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/21 02:10:36 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 2200
# define HEIGHT 1300

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			xr;
	int			yr;
	int			c;
}				t_point;

typedef struct	s_options
{
	int			color;
	int			moveh;
	int			moveb;
	int			moved;
	int			moveg;
	int			view;
	int			zoom;
}				t_options;

typedef struct	s_struct
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_str;
	int			*str;
	t_point		**map;
	int			nb_col;
	int			nb_l;
	t_options	options;
}				t_struct;

void			draw_line(t_struct *param, int i, int j);
void			draw_point(t_struct *param);
void			free_map(t_point **map);
int				main2(int argc, const char **argv);
char			*ornaments(char *str, int c);
void			save_map(t_struct *info, int fd, const char *file, int nb_l);
int				x2calculation(t_struct *p, int i, int j, int choice);
int				y2calculation(t_struct *p, int i, int j, int choice);

#endif
