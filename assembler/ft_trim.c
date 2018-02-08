/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:50:22 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/08 16:33:53 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	ft_frontspace_len(char *str)
{
	int		i;
	int		space_len;

	i = 0;
	space_len = 0;
	while (str[i] && ft_isspace(str[i]))
	{
		space_len++;
		i++;
	}
	return (space_len);
}

static int	ft_endspace_len(char *str)
{
	int		i;
	int		space_len;

	i = ft_strlen(str) - 1;
	space_len = 0;
	while (str[i] && ft_isspace(str[i]))
	{
		space_len++;
		i--;
	}
	return (space_len);
}

char		*ft_trim(char *str)
{
	char	*new_str;
	int		front_len;
	int		new_len;
	int		i;

	front_len = ft_frontspace_len(str);
	new_len = ft_strlen(str) - front_len - ft_endspace_len(str);
	if (new_len < 1)
		return (NULL);
	if (!(new_str = ft_strnew(new_len)))
		ft_error("ft_strnew failed in ft_trim");
	i = 0;
	while (i < new_len)
		new_str[i++] = str[front_len++];
	return (new_str);
}
