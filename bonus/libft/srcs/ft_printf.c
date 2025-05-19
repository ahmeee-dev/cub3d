/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:21:46 by apintaur          #+#    #+#             */
/*   Updated: 2025/01/14 11:40:38 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_utils.h"
#include <stdarg.h>
#include <limits.h>

static int	ft_switch(const char c, va_list *lst);

int	ft_printf(const char *s, ...)
{
	va_list			lst;
	size_t			i;
	int				j;

	if (!s || !*s)
		return (0);
	i = 0;
	j = 0;
	va_start(lst, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			j += ft_switch(s[i + 1], &lst);
			i++;
		}
		else
			j += ft_printchar(s[i]);
		i++;
	}
	va_end(lst);
	return (j);
}

static int	ft_switch(const char c, va_list *lst)
{
	if (c == 'c')
		return (ft_printchar((char)va_arg(*lst, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(*lst, char *)));
	else if (c == 'p')
		return (ft_printptr(va_arg(*lst, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(*lst, int), DEC));
	else if (c == 'u')
		return (ft_printnbr(va_arg(*lst, unsigned int), UINT));
	else if (c == 'x')
		return (ft_printnbr(va_arg(*lst, unsigned int), HEX_LW));
	else if (c == 'X')
		return (ft_printnbr(va_arg(*lst, unsigned int), HEX_UP));
	else if (c == '%')
		return (ft_printchar('%'));
	return (0);
}
