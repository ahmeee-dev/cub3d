/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:23:40 by apintaur          #+#    #+#             */
/*   Updated: 2025/01/14 11:40:53 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_utils.h"

int	ft_putnbr_base(const long long int nbr, const char *base)
{
	long long int			n;
	int						real_base;
	int						nbrlen;

	nbrlen = 0;
	n = nbr;
	real_base = ft_strlen(base);
	if (n < 0)
	{
		n = -n;
		nbrlen = ft_printchar('-');
	}
	if (n > real_base - 1)
		nbrlen += ft_putnbr_base(n / real_base, base);
	ft_putchar_fd(base[n % real_base], 1);
	return (nbrlen + 1);
}

int	ft_putunbr_base(const unsigned long long nbr, const char *base)
{
	unsigned long long	n;
	unsigned int		real_base;
	int					nbrlen;

	nbrlen = 0;
	n = nbr;
	real_base = ft_strlen(base);
	if (n > real_base - 1)
		nbrlen += ft_putnbr_base(n / real_base, base);
	ft_putchar_fd(base[n % real_base], 1);
	return (nbrlen + 1);
}
