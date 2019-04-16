/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:21:27 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/21 02:07:26 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int			x2_y2_calculation(t_struct *p, int i, int j, int choice)
{
	if (choice == 11)
		return (p->map[i - 1][j].xr);
	if (choice == 12)
		return (p->map[i][j - 1].xr);
	if (choice == 21)
		return (p->map[i - 1][j].yr);
	if (choice == 22)
		return (p->map[i][j - 1].yr);
	return (0);
}

static void	draw_case_one(t_struct *p, int i, int j, int choice)
{
	int x;
	int x2;
	int y2;
	int calc;

	x2 = x2_y2_calculation(p, i, j, choice + 10);
	y2 = x2_y2_calculation(p, i, j, choice + 20);
	if (x2 < p->map[i][j].xr)
	{
		x = x2 - 1;
		while (++x <= p->map[i][j].xr && (calc = x + (WIDTH * (p->map[i][j].yr
			+ (y2 - p->map[i][j].yr) * (x - p->map[i][j].xr)
			/ (x2 - p->map[i][j].xr)))) < WIDTH * HEIGHT)
			if (calc >= 0 && x >= 0 && x < WIDTH)
				p->str[calc] = p->map[i][j].c;
	}
	else
	{
		x = p->map[i][j].xr - 1;
		while (++x <= x2 && (calc = (x + (WIDTH * (p->map[i][j].yr +
			(y2 - p->map[i][j].yr) * (x - p->map[i][j].xr)
			/ (x2 - p->map[i][j].xr))))) < WIDTH * HEIGHT)
			if (calc >= 0 && x >= 0 && x < WIDTH)
				p->str[calc] = p->map[i][j].c;
	}
}

static void	draw_case_two(t_struct *p, int i, int j, int choice)
{
	int y;
	int x2;
	int y2;
	int calc;

	x2 = x2_y2_calculation(p, i, j, choice + 10);
	y2 = x2_y2_calculation(p, i, j, choice + 20);
	if (y2 < p->map[i][j].yr)
	{
		y = y2 - 1;
		while (++y <= p->map[i][j].yr && ((calc = (p->map[i][j].xr
			+ (x2 - p->map[i][j].xr) * (y - p->map[i][j].yr)
			/ (y2 - p->map[i][j].yr))) + (WIDTH * y)) < WIDTH * HEIGHT)
			if (calc + WIDTH * y >= 0 && calc < WIDTH)
				p->str[calc + WIDTH * y] = p->map[i][j].c;
	}
	else
	{
		y = p->map[i][j].yr - 1;
		while (++y <= y2 && (calc = (p->map[i][j].xr + (x2 - p->map[i][j].xr)
			* (y - p->map[i][j].yr) / (y2 - p->map[i][j].yr)))
			+ (WIDTH * y) < WIDTH * HEIGHT)
			if (calc + WIDTH * y >= 0 && calc < WIDTH)
				p->str[calc + WIDTH * y] = p->map[i][j].c;
	}
}

static void	draw_line_two_cases(t_struct *p, int i, int j, int choice)
{
	int x2;
	int y2;
	int dx;
	int dy;

	if (choice == 1)
	{
		x2 = p->map[i - 1][j].xr;
		y2 = p->map[i - 1][j].yr;
	}
	if (choice == 2)
	{
		x2 = p->map[i][j - 1].xr;
		y2 = p->map[i][j - 1].yr;
	}
	dx = abs(p->map[i][j].xr - x2);
	dy = abs(p->map[i][j].yr - y2);
	if (dx >= dy)
		draw_case_one(p, i, j, choice);
	if (dy >= dx)
		draw_case_two(p, i, j, choice);
}

void		draw_line(t_struct *p, int i, int j)
{
	while (p->map[++i])
	{
		j = -1;
		while (++j < p->nb_col)
		{
			if (p->map[i][j].c == 0 || p->map[i][j].c == 0x90EE90
				|| p->map[i][j].c == 0xAFEEEE || p->map[i][j].c == 0xFF444F
				|| p->map[i][j].c == 0xFFD700 || p->map[i][j].c == 0x8C90A7)
				p->map[i][j].c = p->options.color;
			if (i - 1 >= 0 && j >= 0)
			{
				draw_line_two_cases(p, i, j, 1);
			}
			if (j - 1 >= 0 && i >= 0)
			{
				draw_line_two_cases(p, i, j, 2);
			}
		}
	}
}
