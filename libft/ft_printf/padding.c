/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:58:17 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/12 18:28:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_spaces(char *tmp, t_printf *t)
{
	int		len;
	char	*str;
	int		i;

	i = -1;
	len = t->nb - ft_strlen(tmp);
	if (len > 0)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (len--)
			str[++i] = ' ';
		return (str);
	}
	if (!(str = ft_strnew(0)))
		return (NULL);
	return (str);
}

static char		*ft_zeros(char *tmp, t_printf *t)
{
	int		len;
	char	*str;
	int		i;

	i = -1;
	len = t->prec - ft_strlen(tmp);
	t->zero = (t->prec && tmp[0] != '-') ? 0 : t->zero;
	if (len > 0)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (len--)
			str[++i] = '0';
		return (str);
	}
	if (!(str = ft_strnew(0)))
		return (NULL);
	return (str);
}

static char		*ft_zerosnb(char *tmp, t_printf *t)
{
	char	*str;
	char	*tm;
	int		i;

	i = ft_strlen(tmp);
	tm = (tmp[0] == '-') ? ft_strsub(tmp, 1, i) : ft_strdup(tmp);
	i = t->nb - ft_strlen(tm);
	i -= (t->space || (t->plus && tmp[0] != '-')) ? 1 : 0;
	i -= (t->hash) ? 2 : 0;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i > 0)
		str[--i] = '0';
	tm = ft_strjoinclr(str, tm, 0);
	tm[0] = (tmp[0] == '-') ? '-' : tm[0];
	free(tmp);
	return (tm);
}

char			*ft_hdl_bis(char *tm, t_printf *t)
{
	char	*df;

	df = NULL;
	df = (tm && t->prec > 0 && ft_charinset(t->flag, "sS")) ?
		ft_strsub(tm, 0, t->prec) : ft_strdup(tm);
	df = (df && t->prec > 0 && ft_charinset(t->flag, "pibdDxXoOuU")) ?
		ft_strjoinclr(ft_zeros(df, t), df, 0) : df;
	df = (df && t->nb > (int)ft_strlen(df) && t->zero == '1') ?
		ft_zerosnb(df, t) : df;
	df = (df && t->hash && ft_charinset(t->flag, "xp") && (ft_atoi(tm) != 0 ||
		t->flag == 'p')) ? ft_strjoinclr("0x", df, 2) : df;
	df = (df && t->hash && t->flag == 'X' && tm[0] != '0' && tm[0]) ?
		ft_strjoinclr("0X", df, 2) : df;
	df = (df && t->hash && ft_charinset(t->flag, "oO") && df[0] != '0') ?
		ft_strjoinclr("0", df, 2) : df;
	df = (df && t->plus && ft_atoi(tm) >= 0 && ft_charinset(t->flag, "di")) ?
		ft_strjoinclr("+", df, 2) : df;
	df = (df && t->neg && t->prec && df[0] != '-') ?
		ft_strjoinclr("-", df, 2) : df;
	df = (df && t->space && !t->neg && (ft_atoi(tm) != 0 || tm[0] == '0') &&
!(t->plus) && !ft_charinset(t->flag, "puoxX")) ? ft_strjoinclr(" ", df, 2) : df;
	df = (df && t->nb > 0 && !(t->minus) && t->z != '1') ?
		ft_strjoinclr(ft_spaces(df, t), df, 0) : df;
	return ((df && t->nb > 0 && t->minus) ?
		ft_strjoinclr(df, ft_spaces(df, t), 0) : df);
}

char			*ft_handler(char *buff, char *tmp, va_list args, int *len)
{
	t_printf	*t;
	char		*tm;
	char		*df;
	int			idx;

	idx = ft_strspn(tmp, " #+-.0123456789hljz");
	df = NULL;
	t = ft_xtractor(tmp, idx);
	if (!(tm = ft_charargs(t, args)))
	{
		ft_dfree(buff, t);
		*len = -1;
		return (NULL);
	}
	df = ft_handler_bis(tm, t, len);
	tm = (!df[0]) ? ft_strjoinclr(buff, "", 1) : ft_strjoinclr(buff, df, 1);
	if (t->z == '1' && t->nb > 1)
	{
		tm = ft_strmjoin(tm, "\0", ft_strlen(tm), 1);
		*len += 1;
	}
	if (df[0])
		*len += ft_strlen(df);
	ft_dfree(df, t);
	return (tm);
}
