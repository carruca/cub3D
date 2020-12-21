/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tab_rem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:43:30 by tsierra-          #+#    #+#             */
/*   Updated: 2020/11/27 14:04:54 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_no_tab(char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t')
			len++;
		i++;
	}
	return (len);
}

char			*ft_str_tab_rem(char *str)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen_no_tab(str);
	if (!(copy = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t')
		{
			copy[len] = str[i];
			len++;
		}
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
