/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:29:37 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/07 18:49:45 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/op.h"

char	*ft_remove_space(char *str)
{
	int		new_len;
	int		i;
	int		j;
	char	*new_str;

	new_len = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			new_len++;
		i++;
	}
	if (!(new_str = ft_strnew(new_len)))
		ft_error("");
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			new_str[j++] = str[i];
		i++;
	}
	ft_printf("%s\n", new_str);
	return (new_str);
}

char	*ft_one_space(char *str)
{
	int		new_len;
	int		i;
	int		j;
	char	*new_str;

	new_len = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			new_len++;
		i++;
	}
	if (!(new_str = ft_strnew(new_len)))
		ft_error("");
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			new_str[j++] = str[i];
		i++;
	}
	ft_printf("%s\n", new_str);
	return (new_str);
}
