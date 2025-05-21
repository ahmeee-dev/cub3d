/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_proc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:23:10 by apintaur          #+#    #+#             */
/*   Updated: 2025/01/14 11:41:07 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_utils.h"
#include <limits.h>

int	ft_printchar(const char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
		ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_printptr(const void *ptr)
{
	unsigned long long	p;
	int					nbrlen;

	if (!ptr)
		return (ft_printstr("(nil)"));
	if ((long int)ptr == LONG_MIN)
		return (ft_printstr("0x8000000000000000"));
	if ((long unsigned int)ptr == ULONG_MAX)
		return (ft_printstr("0xffffffffffffffff"));
	nbrlen = 0;
	p = (unsigned long long)ptr;
	if (p == ULONG_MAX)
		nbrlen++;
	ft_putstr_fd("0x", 1);
	nbrlen += ft_putnbr_base(p, "0123456789abcdef") + 2;
	return (nbrlen);
}

int	ft_printnbr(const long long int nbr, const int which)
{
	int	nbrlen;

	nbrlen = 0;
	if (which == DEC)
		nbrlen += ft_putnbr_base(nbr, "0123456789");
	else if (which == HEX_UP)
		nbrlen += ft_putunbr_base(nbr, "0123456789ABCDEF");
	else if (which == HEX_LW)
		nbrlen += ft_putunbr_base(nbr, "0123456789abcdef");
	else if (which == UINT)
		nbrlen += ft_putunbr_base(nbr, "0123456789");
	return (nbrlen);
}
