/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:19:32 by apintaur          #+#    #+#             */
/*   Updated: 2025/02/22 13:38:47 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# define DEC 1
# define UINT 2
# define HEX_LW 3
# define HEX_UP 4

# include "libft.h"
# include <stddef.h>

int	ft_printchar(const char c);
int	ft_printstr(char *str);
int	ft_printptr(const void *ptr);
int	ft_printnbr(const long long int nbr, const int which);
int	ft_putnbr_base(const long long int nbr, const char *base);
int	ft_putunbr_base(const unsigned long long nbr, const char *base);

#endif
