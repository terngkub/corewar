/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:50:22 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/07 20:51:39 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		ft_frontspace_len(char *str)
{
	int		i;
	int		space_len;

	i = 0;
	space_len = 0;
	while (ft_isspace(str[i++]))
		space_len++;
	return (space_len);
}

int		ft_endspace_len(char *str)
{
	int		i;
	int		space_len;

	i = ft_strlen(str) - 1;
	space_len = 0;
	while (ft_isspace(str[i--]))
		space_len++;
	return (space_len);
}

void	ft_trim(char **str)
{
	int		front_len;
	int		end_len;
	int		new_len;
	char	*temp;
	char	*new_str;
	int		i;

	temp = *str;
	front_len = ft_frontspace_len(temp);
	end_len = ft_endspace_len(temp);
	new_len = ft_strlen(temp) - front_len - end_len;
	new_str = ft_strnew(new_len);
	i = 0;
	while (i < new_len)
		new_str[i++] = temp[front_len++];
	*str = new_str;
}

/*
int		ft_onespace_len(char *str)
{
	int		i;
	int		new_len;
	char	first_space;

	i = 0;
	new_len = 0;
	first_space = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			new_len++;
			first_space = 1;
		}
		else if (first_space)
		{
			new_len++;
			first_space = 0;
		}
		i++;
	}
	return (new_len);
}

char	*ft_onespace(char *str)
{
	int		i;
	int		j;
	int		first_space;
	char	*new_str;
	
	ft_trimspace(&str);
	new_str = ft_strnew(ft_onespace_len(str));
	i = 0;
	j = 0;
	first_space = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			new_str[j++] = str[i];
			first_space = 1;
		}
		else if (first_space)
		{
			new_str[j++] = ' ';
			first_space = 0;
		}
		i++;
	}
	return (new_str);
}

int		main(void)
{
	ft_printf("%s\n", ft_onespace("   abc   	def 		   ghi   		  "));
	return (0);
}
*/
