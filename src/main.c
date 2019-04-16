/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:21:04 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/21 02:20:54 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		key_hook2(int key, t_struct *param)
{
	if (key == 53)
	{
		free_map(param->map);
		exit(0);
	}
	if (key == 5)
		param->options.color = 0x90EE90;
	if (key == 11)
		param->options.color = 0xAFEEEE;
	if (key == 15)
		param->options.color = 0xFF444F;
	if (key == 16)
		param->options.color = 0xFFD700;
	if (key == 34)
		param->options.view = 1;
	if (key == 35)
		param->options.view = 2;
	draw_point(param);
	ft_putnbr(key);
	ft_putchar('\n');
	return (0);
}

static int		key_hook(int key, t_struct *param)
{
	if (key == 24)
		param->options.zoom += 2;
	if (key == 27)
	{
		if (param->options.zoom - 2 > 0)
			param->options.zoom -= 2;
	}
	if (key == 126)
		param->options.moveh += 10;
	if (key == 125)
		param->options.moveb -= 10;
	if (key == 124)
		param->options.moved -= 10;
	if (key == 123)
		param->options.moveg += 10;
	draw_point(param);
	ft_putnbr(key);
	ft_putchar('\n');
	key_hook2(key, param);
	return (0);
}

static int		mouse_hook(int button, int x, int y, t_struct *param)
{
	int alpha;
	int c;
	int r;

	c = 0xFFFFFF;
	r = 50;
	if (button == 1)
	{
		alpha = 0;
		r += 4;
		while (alpha <= 360)
		{
			mlx_pixel_put(param->mlx_ptr, param->win_ptr, x + r * cos(alpha),
					y + r * sin(alpha), c);
			alpha++;
			c += 1000000;
		}
	}
	if (button == 2)
		mlx_pixel_put(param->mlx_ptr, param->win_ptr, x, y, 0x00F532);
	ft_putnbr(button);
	return (0);
}

static void		window(t_struct info)
{
	info.options.color = 0x8C90A7;
	info.options.view = 0;
	if (info.nb_col <= 20 && info.nb_col > 0)
		info.options.zoom = 27;
	else if (info.nb_col > 20 && info.nb_col <= 80)
		info.options.zoom = 5;
	else if (info.nb_col > 80 && info.nb_col <= 140)
		info.options.zoom = 3;
	else if (info.nb_col > 140 && info.nb_col <= 200)
		info.options.zoom = 3;
	else
		info.options.zoom = 1;
	info.options.moveh = 0;
	info.options.moveb = 0;
	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, WIDTH, HEIGHT, "FdF");
	mlx_key_hook(info.win_ptr, key_hook, &info);
	mlx_mouse_hook(info.win_ptr, mouse_hook, &info);
	draw_point(&info);
	mlx_loop(info.mlx_ptr);
}

int				main(int argc, const char **argv)
{
	int			fd;
	t_struct	info;

	if (argc != 2)
	{
		ft_putendl("error, need one argument");
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("error, the argument must be a valid file");
		return (1);
	}
	if (WIDTH > 2500 || WIDTH < 1000 || HEIGHT > 1300 || HEIGHT < 500)
	{
		ft_putendl("error, wrong size of window");
		return (1);
	}
	save_map(&info, fd, argv[1], 0);
	window(info);
	free_map(info.map);
	return (0);
}
