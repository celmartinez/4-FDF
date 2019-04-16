/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 23:58:08 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/15 01:58:07 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void		free_map(t_point **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i++]);
	}
	free(map);
}
