/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <pnardozi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:21:19 by pnardozi          #+#    #+#             */
/*   Updated: 2018/02/15 14:20:47 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int start, int end)
{
	char	*dest;
	int		i;

	i = 0;
	if (s)
	{
		if (!(dest = ft_strnew(end - start)))
			return (0);
		while (start != end + 1)
		{
			dest[i] = s[start];
			start++;
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
	return (NULL);
}
