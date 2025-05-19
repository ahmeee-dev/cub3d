/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:30:57 by apintaur          #+#    #+#             */
/*   Updated: 2025/01/14 11:23:18 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (!str1)
		return (str2[i]);
	if (!str2)
		return (str1[i]);
	if (n != 0)
	{
		while ((str1[i] == str2[i]) && i < n - 1)
			i++;
		return (str1[i] - str2[i]);
	}
	return (0);
}
