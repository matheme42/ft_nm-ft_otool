/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cpu_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 17:02:58 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:16:08 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/misc.h"

/*
** https://opensource.apple.com/source/cctools/cctools-410.1/libstuff/arch.c.auto.html
*/

static const t_arch_info g_arch_info_table[] = {
	{"any", CPU_TYPE_ANY, CPU_SUBTYPE_MULTIPLE, UNKNOWN},
	{"arm", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_ALL, LITTLE},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_ALL, LITTLE},
	{"arm64", CPU_TYPE_ARM64, CPU_SUBTYPE_ARM64_V8, LITTLE},
	{"armv4t", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V4T, LITTLE},
	{"armv5", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V5TEJ, LITTLE},
	{"armv6", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6, LITTLE},
	{"armv6m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V6M, LITTLE},
	{"armv7", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7, LITTLE},
	{"armv7em", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7EM, LITTLE},
	{"armv7f", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7F, LITTLE},
	{"armv7k", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7K, LITTLE},
	{"armv7m", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7M, LITTLE},
	{"armv7s", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V7S, LITTLE},
	{"armv8", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_V8, LITTLE},
	{"big", CPU_TYPE_ANY, CPU_SUBTYPE_BIG_ENDIAN, BIG},
	{"hppa", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_ALL, BIG},
	{"hppa7100LC", CPU_TYPE_HPPA, CPU_SUBTYPE_HPPA_7100LC, BIG},
	{"i386", CPU_TYPE_I386, CPU_SUBTYPE_I386_ALL, LITTLE},
	{"i486", CPU_TYPE_I386, CPU_SUBTYPE_486, LITTLE},
	{"i486SX", CPU_TYPE_I386, CPU_SUBTYPE_486SX, LITTLE},
	{"i586", CPU_TYPE_I386, CPU_SUBTYPE_586, LITTLE},
	{"i686", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO, LITTLE},
	{"i860", CPU_TYPE_I860, CPU_SUBTYPE_I860_ALL, BIG},
	{"little", CPU_TYPE_ANY, CPU_SUBTYPE_LITTLE_ENDIAN, LITTLE},
	{"m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY, BIG},
	{"m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040, BIG},
	{"m68k", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL, BIG},
	{"m88k", CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL, BIG},
	{"pentIIm3", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3, LITTLE},
	{"pentIIm5", CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5, LITTLE},
	{"pentium", CPU_TYPE_I386, CPU_SUBTYPE_PENT, LITTLE},
	{"pentium4", CPU_TYPE_I386, CPU_SUBTYPE_PENTIUM_4, LITTLE},
	{"pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO, LITTLE},
	{"ppc", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL, BIG},
	{"ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601, BIG},
	{"ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603, BIG},
	{"ppc603e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e, BIG},
	{"ppc603ev", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603ev, BIG},
	{"ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604, BIG},
	{"ppc604e", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e, BIG},
	{"ppc64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL, BIG},
	{"ppc7450", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450, BIG},
	{"ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750, BIG},
	{"ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970, BIG},
	{"ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970, BIG},
	{"sparc", CPU_TYPE_SPARC, CPU_SUBTYPE_SPARC_ALL, BIG},
	{"x86_64", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL, LITTLE},
	{"x86_64", CPU_TYPE_X86_64, 0x80000003, LITTLE},
	{"x86_64", CPU_TYPE_I386, CPU_SUBTYPE_X86_64_H, LITTLE},
	{"x86_64", CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_H, LITTLE},
	{"xscale", CPU_TYPE_ARM, CPU_SUBTYPE_ARM_XSCALE, LITTLE},
	{NULL, 0, 0, 0}
};

t_arch_info	get_arch_info_from_cpu_type(cpu_type_t cputype,
													cpu_subtype_t cpusubtype)
{
	int		index;

	index = -1;
	while (g_arch_info_table[++index].name)
	{
		if (g_arch_info_table[index].cputype == cputype &&
							g_arch_info_table[index].cpusubtype == cpusubtype)
			break ;
	}
	return (g_arch_info_table[index]);
}
