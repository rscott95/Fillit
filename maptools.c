/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maphelper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscott <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:40:04 by rscott            #+#    #+#             */
/*   Updated: 2018/05/23 13:32:25 by rscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	[solver.c:152] called from solver()
**	frees the map's memory
*/

void	freemap(char **map, int mapside)
{
	int i;

	i = 0;
	while (i < mapside)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/*
**	[solver.c:158] called from solver()
**	prints the map
*/

void	printmap(char **map, int mapside)
{
	int i;

	i = 0;
	while (i < mapside)
	{
		ft_putstr(map[i]);
		ft_putchar('\n');
		i++;
	}
}

/*
**	[solver.c:146] called from solver()
**	finds the map size based on the number of tetrominos
*/

int		setsidesize(int numtetris)
{
	int i;
	int minimum;

	i = 2;
	minimum = numtetris * 4;
	while (minimum > (i * i))
		i++;
	return (i);
}

/*
**	[solver.c:147] called from solver()
**	allocates memory for a 2D array to store the empty map.
**			MAPOFFSET provides extra memory on the right and bottom edges of the
**			map needed for checking the tetrominos. the map is filled with '.'s.
*/

char	**makemap(int mapside, int mapsidewithoffset, int i)
{
	char	**map;
	int		j;

	mapsidewithoffset = mapside + MAPOFFSET;
	map = (char **)malloc(sizeof(char *) * mapsidewithoffset + 1);
	if (!map)
		return (0);
	map[mapsidewithoffset] = 0;
	while (++i < mapside)
	{
		map[i] = ft_strnew(mapsidewithoffset);
		if (!map)
			return (0);
		ft_bzero(map[i], mapsidewithoffset);
		j = -1;
		while (++j < mapside)
			map[i][j] = '.';
	}
	i--;
	while (++i < mapsidewithoffset)
	{
		map[i] = ft_strnew(mapsidewithoffset);
		ft_bzero(map[i], mapsidewithoffset);
	}
	return (map);
}
