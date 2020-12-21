/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:00:00 by tsierra-          #+#    #+#             */
/*   Updated: 2019/11/19 19:10:02 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s2;

	s2 = (void*)s;
	while (*s2 != c)
	{
		if (*s2 == '\0')
			return (NULL);
		s2++;
	}
	return (s2);
}