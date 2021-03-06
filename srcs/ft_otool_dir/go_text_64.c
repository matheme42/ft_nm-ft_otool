/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_text_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 21:20:48 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 13:53:04 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_otool.h"

static void	*go_lc_text_64(t_arch input)
{
	uint64_t				index;
	struct load_command		*lc;
	char					cmp[16];

	lc = input.lc;
	(void)cmp;
	ft_memset(cmp, 0, 16);
	index = -1;
	while (++index < input.ncmds)
	{
		if (ifswap32(&input, lc->cmd) == LC_SEGMENT_64)
		{
			if (!secure_add(input, lc, sizeof(struct segment_command_64)))
				return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
			if (!ft_strncmp(
				((struct segment_command_64 *)lc)->segname, SEG_TEXT, 16) ||
				!ft_memcmp(((struct segment_command_64 *)lc)->segname, cmp, 16))
				return (lc);
		}
		if (!(lc = secure_add_mv(input, lc, ifswap32(&input, lc->cmdsize))))
			break ;
	}
	print_error(input.path, PROGRAM, ERR_MALFORMED);
	return (NULL);
}

static void	*go_sect_text_64(t_arch input, void *offset, uint64_t nb)
{
	uint64_t	index;

	if (!secure_add(input, offset, sizeof(struct section_64)))
	{
		print_error(input.path, PROGRAM, ERR_MALFORMED);
		return (NULL);
	}
	index = -1;
	while (++index < nb)
	{
		if (!secure_add(input, offset, sizeof(struct section_64)))
			return (return_error_null(input.path, PROGRAM, ERR_MALFORMED));
		if (!ft_strncmp(((struct section_64 *)offset)->sectname, SECT_TEXT, 16))
			return (offset);
		if (!(offset = secure_add_mv(input, offset, sizeof(struct section_64))))
			break ;
	}
	print_error(input.path, PROGRAM, ERR_MALFORMED);
	return (NULL);
}

void		*go_text_64(t_arch *input, struct section_64 *sect)
{
	void		*offset;

	if (!(offset = go_lc_text_64(*input)))
		return (NULL);
	if (!secure_add_mv(*input, offset, sizeof(struct segment_command_64)))
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	offset = go_sect_text_64(*input, offset + sizeof(struct segment_command_64),
								((struct segment_command_64 *)offset)->nsects);
	if (!offset)
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	*sect = *((struct section_64 *)offset);
	if (input->is_swap)
		swap_section_64(sect, 1);
	if (!(offset = secure_add_mv(*input, input->data, sect->offset)))
		return (return_error_null(input->path, PROGRAM, ERR_MALFORMED));
	return (offset);
}
