/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:22:11 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/21 01:55:39 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void		free_line(char **line_split)
{
	int i;

	i = 0;
	while (line_split[i])
	{
		free(line_split[i]);
		i++;
	}
	free(line_split);
}

static void		error(int n)
{
	if (n == 1)
		ft_putendl("error, not a valid map");
	if (n == 2)
		ft_putendl("error, not a valid file");
	if (n == 3)
		ft_putendl("error, color is invalid");
	exit(EXIT_FAILURE);
}

static void		create_map2(t_struct *p, int i, int j, char **l_s)
{
	int k;

	while (++j < p->nb_col && l_s[j] != '\0')
	{
		p->map[i][j].x = i;
		p->map[i][j].y = j;
		p->map[i][j].z = ft_atoi(l_s[j]);
		if (p->map[i][j].z > 1000 || p->map[i][j].z < -1000)
			error(1);
		k = 0;
		if (l_s[j][k] == '-')
			k++;
		while (l_s[j][k] >= '0' && l_s[j][k] <= '9')
			k++;
		if (l_s[j][k] == ',' && l_s[j][k + 1] == '0' && l_s[j][k + 2] == 'x')
		{
			if ((p->map[i][j].c = ft_atoi_base(&(l_s[j][k + 3]), 16)) == 0
					|| ft_strlen(&(l_s[j][k + 3])) > 6)
				error(3);
		}
		else if (l_s[j][k] == '\0')
			p->map[i][j].c = 0;
		else
			error(1);
	}
}

static void		create_map(t_struct *info, int fd, int nb_y, int nb_y2)
{
	int		i;
	char	**line_split;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line) > 0 && i < info->nb_l)
	{
		line_split = ft_strsplit(line, ' ');
		free(line);
		while (line_split[nb_y] != NULL)
			nb_y++;
		if (nb_y2 == 0)
			nb_y2 = nb_y;
		if (nb_y != nb_y2)
			error(1);
		if (!(info->map[i] = (t_point *)malloc(sizeof(t_point) * nb_y + 1)))
			exit(EXIT_FAILURE);
		info->nb_col = nb_y;
		create_map2(info, i, -1, line_split);
		free_line(line_split);
		i++;
	}
	free(line);
	if (nb_y == 1)
		error(1);
}

void			save_map(t_struct *info, int fd, const char *file, int nb_lines)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		nb_lines++;
		if (nb_lines > 10000)
			error(1);
		free(line);
	}
	if (ret == -1 || nb_lines <= 1)
		error(2);
	info->nb_l = nb_lines;
	free(line);
	close(fd);
	fd = open(file, O_RDONLY);
	if (!(info->map = (t_point **)malloc(sizeof(t_point *) * nb_lines + 1)))
		exit(EXIT_FAILURE);
	create_map(info, fd, 0, 0);
	info->map[nb_lines] = NULL;
	close(fd);
}
