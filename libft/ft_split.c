/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:01:59 by tsierra-          #+#    #+#             */
/*   Updated: 2019/12/05 18:11:21 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_segment(char const *s, char c)
{
	size_t	counter;
	int		i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		counter++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (counter);
}

static void		*destroy_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != '\0')
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	tab_counter;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	tab_counter = count_segment(s, c);
	if ((strs = (char**)malloc(sizeof(char*) * (tab_counter + 1))) == NULL)
		return (NULL);
	tab_counter = 0;
	j = -1;
	while (s[++j])
	{
		if (s[j] == c)
			continue;
		i = 0;
		while (s[j + i] && s[j + i] != c)
			i++;
		if ((strs[tab_counter++] = ft_strndup(&s[j], i)) == NULL)
			return (destroy_strs(strs));
		j = j + i - 1;
	}
	strs[tab_counter] = NULL;
	return (strs);
}
