/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 02:07:58 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 11:31:37 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strrlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] && s[i] != c)
			i++;
	return (i);
}

size_t	ft_gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src && dst)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		while (src[i])
			i++;
	}
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
		i++;
	new = (char *) malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	ft_gnl_strlcpy(new, s, i + 1);
	return (new);
}

char	*ft_strnjoin(char *s1, char *s2, ssize_t bytes)
{
	char		*new;
	size_t		i;

	if (!s1 && !s2)
		return (malloc(1));
	if (!s1 && s2)
		return (ft_strndup(s2, bytes));
	i = 0;
	if (s1)
		while (s1[i])
			i++;
	if (!s2)
		bytes = 0;
	new = (char *) malloc(sizeof(char) * (i + bytes + 1));
	if (!new)
		return (NULL);
	if (s1)
		ft_gnl_strlcpy(new, s1, i + 1);
	if (s2)
		ft_gnl_strlcpy(&new[i], s2, bytes + 1);
	free (s1);
	return (new);
}

char	*ft_strupdate(char **join, size_t i)
{
	char	*ret;
	char	*tmp;
	size_t	len;

	if (*join && (*join)[0])
	{
		if ((*join)[i])
			i++;
		ret = ft_strndup(*join, i);
		len = 0;
		while ((*join)[len])
			len++;
		tmp = ft_strndup (&((*join)[i]), len);
		free (*join);
		*join = tmp;
		return (ret);
	}
	if (*join)
	{
		free (*join);
		*join = NULL;
	}
	return (NULL);
}
