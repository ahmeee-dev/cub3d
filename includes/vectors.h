/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:12:25 by apintaur          #+#    #+#             */
/*   Updated: 2025/05/13 10:12:26 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
#define VECTORS_H

typedef struct s_color
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_3fpoint
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}	t_3fpoint;

typedef struct s_2fpoint
{
	float	x;
	float	y;
}	t_2fpoint;

typedef struct s_2ipoint
{
	int	x;
	int	y;
}	t_2ipoint;

#endif
