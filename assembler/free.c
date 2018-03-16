/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:35:45 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/16 16:44:45 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		free_labels(t_list **labels)
{
	t_list		*t;

	while (*labels)
	{
		ft_strdel((char**)&((t_label*)(*labels)->content)->name);
		t = (*labels)->next;
		ft_memdel((void**)&(*labels)->content);
		ft_memdel((void**)labels);
		*labels = t;
	}
}

void		free_inst(t_list **inst)
{
	t_list		*t;

	while (*inst)
	{
		ft_free2((void**)((t_inst*)(*inst)->content)->param_arr);
		t = (*inst)->next;
		ft_memdel((void**)&(*inst)->content);
		ft_memdel((void**)inst);
		*inst = t;
	}
}

int			free_return(t_file *f, t_champ *champ, int ret)
{
	ft_strdel(&f->cor_filename);
	if (champ->labels)
		free_labels(&champ->labels);
	free_inst(&champ->inst);
	return (ret);
}
