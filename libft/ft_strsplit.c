/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:07:30 by cmartine          #+#    #+#             */
/*   Updated: 2018/06/20 01:02:50 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			words++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

static char		**ft_filltab(char const *s, char c, char **tab, size_t n)
{
	int		w;
	size_t	i;
	int		j;

	w = 0;
	i = 0;
	if (s[0] == '\0')
	{
		tab[i] = NULL;
		return (tab);
	}
	while (i < n)
	{
		j = 0;
		if (!(tab[i] = malloc(sizeof(char) * ft_strlen(s) + 1)))
			return (NULL);
		while (s[w] == c && s[w] != '\0')
			w++;
		while (s[w] != c && s[w] != '\0')
			tab[i][j++] = s[w++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	n;

	if (s != NULL)
	{
		n = count_words((char *)s, c);
		if (!(tab = malloc(sizeof(char *) * n + 1)))
			return (NULL);
		return (ft_filltab(s, c, tab, n));
	}
	return (NULL);
}
