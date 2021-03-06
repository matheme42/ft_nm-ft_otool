/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:36 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 18:20:00 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISC_H
# define MISC_H

# include "../libft/includes/libft.h"
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <ar.h>

# ifdef __i386__
#  define GET_ARCH "i386"
# endif

# ifdef __x86_64__
#  define GET_ARCH "x86_64"
# endif

# ifdef __ppc__
#  define GET_ARCH "ppc"
# endif

# ifndef __i386__
#  ifndef __ppc__
#   ifndef __x86_64__
#    define GET_ARCH ""
#   endif
#  endif
# endif

typedef enum				e_type_err {
	ERR_INVALID,
	ERR_MALFORMED,
	ERR_UNDIFINED,
	ERR_MALLOC
}							t_type_err;

# define ERR_OPEN_FMT "{red}%s{no}: '%s': open() fail\n"
# define ERR_FSTAT_FMT "{red}%s{no}: fd:'%d' : fstat() fail\n"
# define ERR_IS_DIR_FMT "{red}%s{no}: fd:'%d': it is a directory \n"
# define ERR_MMAP_FMT "{red}%s{no}: fd:'%d' : mmap() fail\n"
# define ERR_INVALID_FMT "{red}%s{no}: The file %s is not valid object file\n"
# define ERR_MALFORMED_FMT "{red}%s{no}: %s truncated or malformed object\n"
# define ERR_MALLOC_FMT "{red}%s{no}: Malloc return Null in %s\n"

void						print_error(const char *path, char *pgm,
															t_type_err type);
int							return_error(const char *path, char *pgm,
													t_type_err type, int ret);
void						*return_error_null(const char *path, char *pgm,
															t_type_err type);

# define MALLOC_LVL_FILE_MACH_O M_LVL_OFFSET + 1

typedef enum				e_endian {
	BIG,
	LITTLE,
	UNKNOWN
}							t_endian;

# ifdef __BIG_ENDIAN__
#  define GET_ENDIAN (t_endian)(BIG)
# endif

# ifdef __LITTLE_ENDIAN__
#  define GET_ENDIAN (t_endian)(LITTLE)
# endif

# define AR_LONG_NAME sizeof(char[20])
# define SIZEOF_OBJ_H  sizeof(struct ar_hdr) + AR_LONG_NAME
# define AR_LEN_BEFORE_SYMTAB SARMAG + SIZEOF_OBJ_H

typedef enum				e_type_macho {
	M_32,
	M_64,
	M_FAT,
	M_FAT_64,
	M_LIB,
	M_END,
	M_ERR
}							t_type_macho;

typedef struct				s_arch {
	const char				*path;
	const void				*data;
	size_t					length;
	uint32_t				magic;
	t_bool					is_swap;
	cpu_type_t				cpu_type;
	cpu_subtype_t			cpu_subtype;
	struct load_command		*lc;
	t_list					*list;
	uint32_t				ncmds;
}							t_arch;

typedef struct				s_handler_func
{
	t_type_macho			type;
	int						(*f)(t_arch *);
}							t_handler_func;

uint16_t					ft_swap_int16(uint16_t x);
uint32_t					ft_swap_int32(uint32_t x);
uint64_t					ft_swap_int64(uint64_t x);

uint16_t					ifswap16(t_arch *input, uint16_t x);
uint32_t					ifswap32(t_arch *input, uint32_t x);
uint64_t					ifswap64(t_arch *input, uint64_t x);

void						swap_fat_header(struct fat_header *fh);
void						swap_mach_header(struct mach_header *mh);
void						swap_mach_header_64(struct mach_header_64 *mh);
void						swap_symtab_command(struct symtab_command *st);
void						swap_section_64(struct section_64 *s,
															uint32_t nsects);
void						swap_section(struct section *s, uint32_t nsects);
void						swap_nlist_64(struct nlist_64 *symbol);
void						swap_nlist(struct nlist *symbol);

int							map_file(const char *prgm, const char *path,
																t_arch *arch);
void						*secure_add(const t_arch input,
										const void *start_add, size_t length);
void						*secure_add_mv(t_arch input, const void *start_add,
																size_t length);
char						*secure_string(t_arch input, char *string_table,
															uint32_t offset);
uint32_t					get_magic(t_arch *arch);
int							get_header_32(const t_arch arch, const void *add,
													struct mach_header *header);
int							get_header_64(const t_arch arch, const void *add,
												struct mach_header_64 *header);
int							get_header_fat(const t_arch arch, const void *add,
													struct fat_header *header);
int							get_header_lib(const t_arch arch, const void *add,
														struct ar_hdr *header);
int							exec_handler(const t_handler_func funcs[],
																t_arch *arch);
t_type_macho				which_header(t_arch *arch);

typedef struct				s_arch_info
{
	const char				*name;
	cpu_type_t				cputype;
	cpu_subtype_t			cpusubtype;
	t_endian				byte_order;
}							t_arch_info;

t_arch_info					get_arch_info_from_cpu_type(cpu_type_t cputype,
													cpu_subtype_t cpusubtype);

#endif
