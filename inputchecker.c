/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputchecker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscott <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:39:48 by rscott            #+#    #+#             */
/*   Updated: 2018/05/23 13:48:38 by rscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** [line 67]	called from shapecheck().
** charcheck() checks if there are only dots and hashes in a single tetromino.
** i is passed into charcheck containing the last index of a tetromino.
** [line 28]	j = 19: the max index in a tetromino, j is subtracted from i
** 		and decremented to check each character of the tetromino.
** [line 37]	hashcount != 4: if there aren't exactly 4 hashes, it is invalid.
*/

int		charcheck(char *buf, int i, int hashcount)
{
	int j;

	j = 19;
	while (j >= 0)
	{
		if (buf[i - j] != '#' && buf[i - j] != '.' && buf[i - j] != '\n')
			return (0);
		if (buf[i - j] == '#')
			hashcount++;
		j--;
	}
	if (hashcount != 4)
		return (0);
	return (1);
}

/*
** [fillit.c:77] called from tetriread()
** [lines 53-60] iterates through the input and checks for a '\n' after each 4
** 		characters in each line of the tetrominos, heightcount adds 1 per line
** [lines 62-71] at the end of a tetri, run charcheck() at the end of the 4th
** 		line of the tetromino (i - 1). then check if there's any data at the
**		current index [line 67] and if not then this is the end of the input.
** [lines 71-75] if a '\n' is found then reset heightcount and continue to the
**		next index which will be the start of the next tetromino.
*/

int		shapecheck(char *buf, int i, int widthcount, int heightcount)
{
	while (buf[++i])
	{
		if (widthcount % 4 == 0 && i > 0)
		{
			heightcount++;
			widthcount = 0;
			if (buf[i] != '\n')
				return (0);
			i++;
		}
		if (heightcount == 4)
		{
			if (charcheck(buf, i - 1, 0) == 0)
				return (0);
			if (!buf[i])
				return (1);
			if (buf[i] != '\n')
				return (0);
			heightcount = 0;
			i++;
		}
		widthcount++;
	}
	return (1);
}

/*
** [line 131] called from inputchecker(), returns a 2d array of tetrominos
** [lines 95-97] creates the top array of a 2D array to hold the tetrominos
** [lines 98-112] creates new strings at 20 length (the size of a tetromino)
** 		and copies the data line by line from the input stored in buf
*/

char	**tetricpy(char *buf, int numberoftetris, int i)
{
	int		j;
	int		row;
	char	**twodarr;

	row = 0;
	if (!(twodarr = (char**)malloc(sizeof(char *) * numberoftetris + 1)))
		return (0);
	twodarr[numberoftetris] = 0;
	while (row < numberoftetris)
	{
		j = 0;
		twodarr[row] = ft_strnew(20);
		while (j < 16)
		{
			if (buf[i] != '\n')
			{
				twodarr[row][j] = buf[i];
				j++;
			}
			i++;
		}
		row++;
	}
	return (twodarr);
}

/*
** [fillit.c:119]	called from main.
** returns a 2d array of the valid tetrominos in the proper format.
** [line 131] splits the tetrominos from the input file into a 2D array
** [lines 132-143] for each tetromino, checks if it matches with one of the
** 		valid possible tetromino shapes in combos. the contents of the tetromino
**		stored in separatedtetris is erased and replaced with the valid shape
**		found (this removes all unneeded '.'s). switches the hashes to letters.
*/

char	**inputchecker(char *buf, int numtetris, char combos[20][15], int row)
{
	char	**separatedtetris;
	int		i;

	separatedtetris = tetricpy(buf, numtetris, 0);
	while (separatedtetris[++row])
	{
		i = 0;
		while (i < 19 && row < numtetris)
		{
			if ((ft_strstr(separatedtetris[row], combos[i]) != 0))
			{
				ft_bzero(separatedtetris[row], ft_strlen(separatedtetris[row]));
				ft_strcpy(separatedtetris[row], combos[i]);
				hashtoletter(separatedtetris[row], row);
				break ;
			}
			else
			{
				if (i == 18)
					return (0);
				i++;
			}
		}
	}
	return (separatedtetris);
}
