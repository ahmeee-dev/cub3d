/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:08:59 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/06 17:51:13 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f) (unsigned int, char))
{
	char			*new;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (malloc(1));
	new = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new == NULL)
		return (NULL);
	if (f != NULL)
	{
		while (s[i] != '\0')
		{
			new[i] = f(i, ((char *)s)[i]);
			i++;
		}
		new[i] = '\0';
	}
	else
		ft_strlcpy(new, s, sizeof(s));
	return (new);
}
