/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 00:28:06 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/21 02:18:37 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int			ft_atoi_base(const char *str, int base)
{
	int				i;
	unsigned long	rslt;
	int				ngtv;

	i = 0;
	rslt = 0;
	ngtv = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
			i++;
		if (str[i] == '+')
			i++;
		if ((str[i] == '-' && str[i - 1] != '+'))
			i++;
		while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a'
		&& str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F'))
			rslt = rslt * base + value(str[i++]);
		if (str[i] != '\0')
			return (0);
		return (rslt);
	}
	return (0);
}
