/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:18:44 by arobion           #+#    #+#             */
/*   Updated: 2018/02/27 16:23:25 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				valid_ocp(unsigned char ocp)
{
	unsigned char	comp;

	comp = ocp >> 6;
	if (comp != 1)
		return (-1);
	comp = ocp << 2;
	comp = comp >> 6;
	if (comp == 1)
		return (0);
	if (comp == 3)
		return (1);
	return (-1);
}

static int		change_move_pc(int val)
{
	if (val == 0)
		return (0);
	if (val == 1)
		return (1);
	if (val == 2)
		return (4);
	if (val == 3)
		return (2);
	return (0);
}

int				modif_pc(unsigned char ocp)
{
	int				ret;
	unsigned char	comp;

	ret = 0;
	comp = ocp >> 6;
	ret += change_move_pc(comp);
	comp = ocp << 2;
	comp = comp >> 6;
	ret += change_move_pc(comp);
	return (ret);
}
