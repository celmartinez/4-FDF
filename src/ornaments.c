/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ornaments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:22:04 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/15 02:17:11 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int			*fill_with_color(int *str, int x, int y, int c)
{
	if (str[x + WIDTH * y] != c)
	{
		str[x + WIDTH * y] = c;
		if (str[x + 1 + WIDTH * y] != c)
			str = fill_with_color(str, x + 1, y, c);
		if (str[x - 1 + WIDTH * y] != c)
			str = fill_with_color(str, x - 1, y, c);
		if (str[x + WIDTH * (y + 1)] != c)
			str = fill_with_color(str, x, y + 1, c);
		if (str[x + WIDTH * (y - 1)] != c)
			str = fill_with_color(str, x, y - 1, c);
	}
	return (str);
}

static int			*buttons_click(int *str, int x, int y, int c)
{
	int alpha;
	int r;
	int x1;
	int y1;

	alpha = 0;
	r = 15;
	x1 = x;
	y1 = y;
	while (alpha <= 360)
	{
		x = x + r * cos(alpha);
		y = y + r * sin(alpha);
		str[x + (WIDTH * y)] = c;
		alpha++;
		x = x1;
		y = y1;
	}
	return (str);
}

static int			*borders(int *str, int c)
{
	int x;
	int y;
	int y2;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < 40)
		{
			str[x + (WIDTH * y)] = c;
			y++;
		}
		y2 = HEIGHT - 70;
		while (y2 < HEIGHT)
		{
			str[x + (WIDTH * y2)] = c;
			y2++;
		}
		x++;
	}
	return (str);
}

static int			*draw_buttons(int *str2)
{
	int x;
	int y;

	x = 35;
	y = HEIGHT - 35;
	str2 = buttons_click(str2, x, y, 0);
	str2 = fill_with_color(str2, x, y, 0);
	x = 235;
	str2 = buttons_click(str2, x, y, 0);
	str2 = fill_with_color(str2, x, y, 0);
	x = WIDTH / 2 + 250;
	str2 = buttons_click(str2, x, y, 0);
	str2 = fill_with_color(str2, x, y, 0);
	x = WIDTH / 2 + 290;
	str2 = buttons_click(str2, x, y, 0);
	str2 = fill_with_color(str2, x, y, 0);
	x = WIDTH / 2;
	while (x <= WIDTH / 2 + 130)
	{
		str2 = buttons_click(str2, x, y, 0);
		str2 = fill_with_color(str2, x, y, 0);
		x = x + 40;
	}
	return (str2);
}

char				*ornaments(char *str, int c)
{
	int x;
	int y;
	int *str2;

	str2 = (int *)str;
	borders(str2, c);
	x = WIDTH - 35;
	y = HEIGHT - 35;
	c = 0xFF444F;
	while (x >= WIDTH - 155)
	{
		str2 = buttons_click(str2, x, y, c);
		str2 = fill_with_color(str2, x, y, c);
		x = x - 40;
		if (c == 0x90EE90)
			c = 0xFFD700;
		if (c == 0xAFEEEE)
			c = 0x90EE90;
		if (c == 0xFF444F)
			c = 0xAFEEEE;
	}
	draw_buttons(str2);
	return ((char *)str2);
}
