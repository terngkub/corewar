/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtract.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:11:01 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/21 21:28:00 by misteir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_xtract_number(const char *str)
{
	int		sign;
	int		a;

	a = 0;
	while (ft_isspace(*str) || *str == '+' || *str == '-' || *str == '#'
			|| *str == '0')
		str++;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '-' || *str == '+') ? 1 : 0;
	while (*str && ft_isdigit(*str))
		a = (a * 10) + (*(str++) - '0');
	return (sign * a);
}

static int		ft_xtract_float(const char *str)
{
	int		a;

	a = 0;
	while ((ft_isspace(*str) || *str == '+' || *str == '-' || *str == '#'
				|| ft_isdigit(*str)) && *str != '.')
		str++;
	if ((!*str || *str == '.') && (str[1] == '0' || !ft_isdigit(str[1])))
		return (-1);
	str++;
	str += (*str == '-' || *str == '+') ? 1 : 0;
	while (*str && ft_isdigit(*str))
		a = (a * 10) + (*(str++) - '0');
	return (a);
}

void			ft_xt_bis(t_printf *t, char *str)
{
	t->prec = ft_xtract_float(str);
	if (t->prec == -1 && ft_charinset(t->flag, "pidDxXoOuU"))
		t->zero = 0;
	if (t->mod1 != t->mod2)
		t->mod2 = 0;
}

t_printf		*ft_xtractor(char *str, int len)
{
	t_printf	*t;
	int			i;

	i = -1;
	t = ft_plst_init();
	t->flag = str[ft_strspn(str, " #+-.0123456789hljz")];
	t->flag = (t->flag == '%') ? 't' : t->flag;
	while (str[++i] && i < len)
	{
		if (!(t->zero) && ft_isdigit(str[i]))
			t->zero = (str[i] > '0') ? '2' : '1';
		t->plus = (!(t->plus) && str[i] == '+') ? '1' : t->plus;
		t->minus = (!(t->minus) && str[i] == '-') ? '1' : t->minus;
		t->hash = (!(t->hash) && str[i] == '#') ? '1' : t->hash;
		t->space = (!(t->space) && str[i] == ' ') ? '1' : t->space;
		if (!(t->mod2) && (t->mod1) && ft_charinset(str[i], "hl"))
			t->mod2 = (str[i] == t->mod1) ? str[i] : t->mod2;
		if ((!(t->mod1) || str[i] == 'l') && ft_charinset(str[i], "hljz"))
			t->mod1 = str[i];
	}
	ft_xt_bis(t, str);
	t->zero = (t->minus) ? 0 : t->zero;
	t->nb = ft_xtract_number(str);
	return (t);
}
