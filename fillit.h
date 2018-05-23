/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscott <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 11:00:22 by rscott            #+#    #+#             */
/*   Updated: 2018/05/23 13:48:13 by rscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define MAPOFFSET 3
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

char	**inputchecker(char *buf, int numtetris, char	combos[20][15],
int row);
int		shapecheck(char *buf, int i, int widthcount, int heightcount);
int		countvalidtetris(char *buf);
int		solver(char **separatedtetris, int numberoftetris);
void	freemap(char **map, int mapside);
void	printmap(char **map, int mapside);
int		setsidesize(int numberoftetris);
char	**makemap(int mapside, int mapsidewithoffset, int i);
char	getletter(char *tetri);
int		hashtoletter(char *validtetri, int row);
#endif
