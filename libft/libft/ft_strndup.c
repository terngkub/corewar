/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:49:39 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/08 21:23:09 by fbabin           ###   ########.fr       */
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
		if (!(dest = ft_strnew(end - start + 1)))
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
