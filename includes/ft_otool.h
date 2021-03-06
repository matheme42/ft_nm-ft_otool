/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 19:18:16 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 18:02:17 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "misc.h"

# define PROGRAM "ft_otool"

typedef struct		s_otool_flags {
	t_bool			print_arch;
	t_handler_func	*funcs;
}					t_otool_flags;

t_otool_flags		*get_otool_flags();
void				*go_text_32(t_arch *input, struct section *sect);
void				*go_text_64(t_arch *input, struct section_64 *sect);
int					intern_nm_parse_option(int ac, const char **av);
int					handler_32(t_arch *input);
int					handler_64(t_arch *input);
void				print_hex(char *start, uint16_t nb, t_bool space,
																t_bool swap);
int					handle_fat(t_arch *input);
int					handle_lib(t_arch *input);
t_bool				print_cpu_type(t_arch *input);

#endif
