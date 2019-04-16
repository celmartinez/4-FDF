/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:21:40 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/20 23:49:44 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void		parallel_view(t_struct *param, int i, int j)
{
	float cte1;

	cte1 = 0.2;
	param->map[i][j].xr = (cte1 * (param->map[i][j].z
				* (param->options.zoom))) + param->map[i][j].x;
	param->map[i][j].yr = (cte1 * (param->map[i][j].z
				* (param->options.zoom))) + (param->map[i][j].y);
}

static void		isometric_view(t_struct *param, int i, int j)
{
	float	cte1;
	float	cte2;

	cte1 = 0.6;
	cte2 = 0.7;
	param->map[i][j].xr = cte1 * param->map[i][j].x - cte2
		* param->map[i][j].y;
	param->map[i][j].yr = (param->map[i][j].z
			* (param->options.zoom)) + (cte1 / 2)
		* param->map[i][j].x + (cte2 / 2) * param->map[i][j].y;
}

static void		save_view_points(t_struct *param, int view, int i)
{
	int j;
	int origin_x;
	int origin_y;

	while (i < param->nb_l)
	{
		origin_y = (HEIGHT / 4) + ((1 * (param)->options.zoom) * i)
			- param->options.moveb - param->options.moveh;
		origin_x = (WIDTH / 2) - ((2 * param->options.zoom) * i)
			- param->options.moveg - param->options.moved;
		j = 0;
		while (j < param->nb_col)
		{
			if (view == 1)
				isometric_view(param, i, j);
			if (view == 2)
				parallel_view(param, i, j);
			param->map[i][j].xr = origin_x - param->map[i][j].xr;
			param->map[i][j].yr = origin_y - param->map[i][j].yr;
			origin_y = origin_y + (1 * param->options.zoom);
			origin_x = origin_x + (2 * param->options.zoom);
			j++;
		}
		i++;
	}
}

static void		choose_view(t_struct *param)
{
	if (param->options.view == 1)
		save_view_points(param, 1, 0);
	if (param->options.view == 2)
		save_view_points(param, 2, 0);
	if (param->options.view != 0)
		draw_line(param, -1, 0);
}

void			draw_point(t_struct *param)
{
	int bpp;
	int size_l;
	int endian;

	param->img_ptr = mlx_new_image(param->mlx_ptr, WIDTH, HEIGHT);
	param->img_str = mlx_get_data_addr(param->img_ptr, &bpp, &size_l, &endian);
	param->str = (int *)param->img_str;
	choose_view(param);
	ornaments((char *)param->str, param->options.color);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0,
			0);
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	mlx_string_put(param->mlx_ptr, param->win_ptr, (WIDTH / 2 - 15), 10, 0,
			"FdF");
	mlx_string_put(param->mlx_ptr, param->win_ptr, (WIDTH - 160),
			HEIGHT - 47, 0, "Y   G   B   R");
	mlx_string_put(param->mlx_ptr, param->win_ptr, 30, HEIGHT - 47,
			param->options.color, "P                   I");
	mlx_string_put(param->mlx_ptr, param->win_ptr, WIDTH / 2 - 5,
			HEIGHT - 47, param->options.color,
			"<   ^   v   >            +   -");
	mlx_string_put(param->mlx_ptr, param->win_ptr, 30,
			HEIGHT - 47, 0, "   Parallel view       Isometric view");
}
