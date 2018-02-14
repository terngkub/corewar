/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:18:27 by arobion           #+#    #+#             */
/*   Updated: 2018/02/14 14:49:27 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process	*lst_new_process(int opc, int cycle, int pc)
{
	t_process	*lst;

	if (!(lst = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	lst->opc = opc;
	lst->cycle_to_wait = cycle;
	lst->pc = pc;
	lst->carry = 0;
	if (!(lst->regs = (char*)malloc(sizeof(char) * (REG_SIZE * REG_NUMBER))))
		exit(0);
	lst->next = NULL;
	return (lst);
}

void	lst_pushfront_process(t_process **begin_list, int opc, int cycle, int pc)
{
	t_process	*lst;

	if (*begin_list)
	{
		lst = lst_new_process(opc, cycle, pc);
		lst->next = *begin_list;
		*begin_list = lst;
	}
	else
		*begin_list = lst_new_process(opc, cycle, pc);
}

void	load_first_champ(t_arena arn, char *champ1)
{
	int		fd;
	char	*l;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(l = ft_strnew(1)))
		exit(0);
	fd = open(champ1, O_RDONLY);
	while (read(fd, l, 1))
	{
		i++;
		if (i > PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		{
			arn.mem[j] = l[0];
			j++;
		}	
	}
}

void	load_second_champ(t_arena arn, char *champ2)
{
	int		fd;
	char	*l;
	int		i;
	int		j;

	i = 0;
	j = MEM_SIZE / 2;
	if (!(l = ft_strnew(1)))
		exit(0);
	fd = open(champ2, O_RDONLY);
	while (read(fd, l, 1))
	{
		i++;
		if (i > PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		{
			arn.mem[j] = l[0];
			j++;
		}
	}
}

int		opc_nb_cycle(int opc)
{
	if (opc == 1)
		return (10);
	if (opc == 2)
		return (5);
	if (opc == 3)
		return (5);
	if (opc == 4)
		return (10);
	if (opc == 5)
		return (10);
	if (opc == 6)
		return (6);
	if (opc == 7)
		return (6);
	if (opc == 8)
		return (6);
	if (opc == 9)
		return (20);
	if (opc == 10)
		return (25);
	if (opc == 11)
		return (25);
	if (opc == 12)
		return (800);
	if (opc == 13)
		return (10);
	if (opc == 14)
		return (50);
	if (opc == 15)
		return (1000);
	if (opc == 16)
		return (2);
	return (1);
}

void	init_process(t_process **begin_list, t_arena arn)
{
	t_process	*lst;

	lst = *begin_list;
	lst = lst_new_process(arn.mem[0], arn.nb_cycle + opc_nb_cycle(arn.mem[0]), 0);
	lst->next = lst_new_process(arn.mem[MEM_SIZE / 2], arn.nb_cycle + opc_nb_cycle(arn.mem[MEM_SIZE / 2]), MEM_SIZE / 2);
}

void	init_arena(t_arena *arn)
{
	(*arn).nb_cycle = 0;
	(*arn).nb_live_1 = 0;
	(*arn).nb_live_2 = 0;
	(*arn).last_live_1 = 0;
	(*arn).last_live_2 = 0;
	(*arn).process = NULL;
	init_process(&(arn->process), *arn);
}

int		main(int argc, char **argv)
{
	t_arena	arn;

	if (argc != 3)
	{
		write(1, "error\n", 6);
		return (0);
	}
	if (!(arn.mem = (char*)malloc(sizeof(char) * MEM_SIZE)))
		exit(0);
	load_first_champ(arn, argv[1]);
	load_second_champ(arn, argv[2]);
	init_arena(&arn);
	print_arena(arn);
	//print_mem(arn.mem);
	return (0);
}
