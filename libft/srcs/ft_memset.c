/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:53:04 by apintaur          #+#    #+#             */
/*   Updated: 2025/01/14 11:14:43 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	k;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	k = (unsigned char)c;
	while (i < n)
	{
		str[i] = k;
		i++;
	}
	return (s);
}
