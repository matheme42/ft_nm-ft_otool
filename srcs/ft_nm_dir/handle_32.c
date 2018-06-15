/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:16:54 by gpouyat           #+#    #+#             */
/*   Updated: 2018/06/15 21:14:19 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"
#include "ft_nm.h"
#include <mach-o/nlist.h>

static t_list		*create_sym(t_arch input, char *string_table, struct nlist sym_table)
{
	t_sym	*elem_sym;
	t_list	*elem;

	if (input.is_swap)
		swap_nlist(&sym_table);
	if (!(elem_sym = (t_sym *)ft_secu_malloc_lvl(sizeof(t_sym), MALLOC_LVL_FILE_MACH_O)))
	{
		ft_dprintf(STDERR_FILENO, "ERROR MALLOC\n");
		return(NULL);
	}
	elem_sym->name = secure_string(input, string_table, sym_table.n_un.n_strx);
	elem_sym->value = sym_table.n_value;
	elem_sym->arch = ARCH_32;
	elem_sym->ntype = sym_table.n_type;
	if (find_seg_sect_name(sym_table, elem_sym, input))
	{
		free(elem_sym);
		return (NULL);
	}
	elem = ft_lstnew(elem_sym, sizeof(t_sym));
	return (elem);
}

static int	loop_get_list_sym(t_arch *input, struct symtab_command sym, struct nlist *array, char *string)
{
	int64_t		index;
	t_list		*new;
	t_list		*lst;

	lst = NULL;
	index = -1;
	while (++index < sym.nsyms)
	{
		new = create_sym(*input, string, array[index]);
		if (!new)
		{
			/*freeALL*/
			return (1);
		}
		ft_lstpush(&lst, new);
	}
	input->list = lst;
	return (0);
}

static t_list	*get_list_syms(struct symtab_command sym, t_arch input)
{
	char			*string;
	struct nlist	*array;

	if (input.is_swap)
		swap_symtab_command(&sym);
	if (!(array = secure_add_mv(input, input.data, sym.symoff)))
	{
		print_error(input.path,PROGRAM, ERR_MALFORMED);
		return (NULL);
	}
	if (!(string = secure_add_mv(input, input.data, sym.stroff)))
	{
		print_error(input.path,PROGRAM, ERR_MALFORMED);
		return (NULL);
	}
	if (!loop_get_list_sym(&input, sym, array, string))
		return(input.list);
	return (NULL);
}

int handler_32(t_arch *input)
{
	struct mach_header header;
	struct	symtab_command	*sym;

	if (get_header_32(*input, input->data, &header))
		return(return_error(input->path, PROGRAM, ERR_INVALID, 2));
	input->ncmds = header.ncmds;
	input->cpu_type = header.cputype;
	input->cpu_subtype = header.cpusubtype;
	if (!(input->lc = secure_add_mv(*input, input->data, sizeof(struct mach_header))))
		return(return_error(input->path, PROGRAM, ERR_INVALID, 2));
	if (!(sym = get_symtab_cmd(*input)))
		return (1);
	input->list = get_list_syms(*sym, *input);
	if (!input->list)
		return (1);
	sort_sym(&(input->list));
	print_nm(input);
	return (0);
}