/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:18:27 by arobion           #+#    #+#             */
/*   Updated: 2018/02/12 19:03:00 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_mem(char *mem)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2hhx ", mem[i]);
		if (i % 16 == 0 && i != 0)
			ft_printf(" \n");
		else if (i % 8 == 0 && i != 0)
			ft_printf(" ");
		i++;
	}
}

void	lst_new_process(int opc, int cycle, int pc)
{
	t_process	*lst;

	if (!(lst = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	lst->opc = opc;
	lst->cycle_to_wait = cycle;
	lst->pc = pc;
	lst->next = NULL;
}

void	lst_pushfront_process(t_process **begin_list, int opc, int cycle, int pc)
{
	t_process	*lst;

	if (*begin_list)
	{
		lst = lst_new_porocess(opc, cycle, pc);
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

void	init_arena(t_arena *arn)
{
	(*arn)->nb_cycle = 0;
	(*arn)->nb_live_1 = 0;
	(*arn)->nb_live_2 = 0;
	(*arn)->last_live_1 = 0;
	(*arn)->last_live_2 = 0;
	(*arn)->carry = 0;
	(*arn)->pc_1 = 0;
	(*arn)->pc_2 = MEM_SIZE / 2;
	(*arn)->process = NULL;
}

void	put_live_in_lst_1(t_arena *arn)
{
	lst_pushfront_propcess(&(arn->process), 1, arn->nb_cycle + 10, arn->pc_1);
	(*arn)->pc_1 += 5;
	(*arn)->pc_1 %= MEM_SIZE;
}

void	get_opc_1(t_arena *arn)
{
	if (mem[pc_1] == 1)
		put_live_in_lst_1(arn);
	if (mem[pc_1] == 2)
		put_ld_in_lst_1(arn);
	if (mem[pc_1] == 3)	
		put_st_in_lst_1(arn);
	if (mem[pc_1] == 4)
		put_add_in_lst_1(arn);
	if (mem[pc_1] == 5)
		put_sub_in_lst_1(arn);
	if (mem[pc_1] == 6)
		put_and_in_lst_1(arn);
	if (mem[pc_1] == 7)
		put_or_in_lst_1(arn);
	if (mem[pc_1] == 8)
		put_xor_in_lst_1(arn);
	if (mem[pc_1] == 9)
		put_zjmp_in_lst_1(arn);
	if (mem[pc_1] == 10)
		put_ldi_in_lst_1(arn);
	if (mem[pc_1] == 11)
		put_sti_in_lst_1(arn);
	if (mem[pc_1] == 12)
		put_fork_in_lst_1(arn);
	if (mem[pc_1] == 13)
		put_lld_in_lst_1(arn);
	if (mem[pc_1] == 14)
		put_lldi_in_lst_1(arn);
	if (mem[pc_1] == 15)
		put_lfork_in_lst_1(arn);
	if (mem[pc_1] == 16)
		put_aff_in_lst_1(arn);
}

int		main(int argc, char **argv)
{
	t_arena	arn;

	init_arena(&arn);
	if (argc != 3)
	{
		write(1, "tamer\n", 6);
		return (0);
	}
	if (!(arn.mem = (char*)malloc(sizeof(char) * MEM_SIZE)))
		exit(0);
	load_first_champ(arn, argv[1]);
	load_second_champ(arn, argv[2]);
	//print_mem(arn.mem);
	get_opc(&arn);	
	return (0);
}
