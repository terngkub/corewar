/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:30:14 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/14 23:32:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_backsearch(char *str, int len)
{
	while (str[--len - 1])
		;
	return (len);
}

char		*ft_handler_bis(char *tm, t_printf *t, int *len)
{
	char	*df;

	df = NULL;
	if (t->prec == -1 && ft_charinset(t->flag, "sS"))
	{
		free(tm);
		tm = ft_strsub(tm, 0, 0);
	}
	df = ft_hdl_bis(tm, t);
	if (*tm)
		free(tm);
	if ((!tm[0] || !df[0]) && ft_charinset(t->flag, "cC"))
	{
		*len += 1;
		if (t->flag == 'c')
			df[1] = '\0';
	}
	return (df);
}

void		ft_dfree(void *s, void *t)
{
	free(s);
	free(t);
}

char		*ft_rep(char *str, char old, char fresh)
{
	int		i;
	char	*fre;

	fre = ft_strnew(ft_strlen(str));
	i = -1;
	while (str[++i])
	{
		if (str[i] == old)
			fre[i] = fresh;
		else
			fre[i] = str[i];
	}
	free(str);
	return (fre);
}
