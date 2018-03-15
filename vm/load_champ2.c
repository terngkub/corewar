/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champ2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:17:21 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/15 15:21:29 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_magic(char *header)
{
	unsigned int	magic;

	magic = x_char_to_int(&header[0], 4);
	if (magic != COREWAR_EXEC_MAGIC)
		return (0);
	return (1);
}

int		check_champ_size(char *header)
{
	long long	ret;

	ret = x_char_to_int(&header[PROG_NAME_LENGTH + 4], 8);
	return (ret);
}
