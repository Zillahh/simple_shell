#include "simple_shell.h"

/**
 * **strtow - It splits a string into words. Repeat delimiters are ignored
 * @strng: the input string
 * @bd: the delimeter string
 * Return: The pointer to an array of strings, or NULL on failure
 */

char **strtow(char *strng, char *bd)
{
	int ai, zmj, zk, zm, numwordz = 0;
	char **bs;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!bd)
		bd = " ";
	for (ai = 0; strng[ai] != '\0'; ai++)
		if (!is_delim(strng[ai], bd) && (is_delim(strng[ai + 1], bd)
					|| !strng[ai + 1]))
			numwordz++;

	if (numwordz == 0)
		return (NULL);
	bs = malloc((1 + numwordz) * sizeof(char *));
	if (!bs)
		return (NULL);
	for (ai = 0, zmj = 0; zmj < numwordz; zmj++)
	{
		while (is_delim(strng[ai], bd))
			ai++;
		zk = 0;
		while (!is_delim(strng[ai + zk], bd) && strng[ai + zk])
			zk++;
		bs[zmj] = malloc((zk + 1) * sizeof(char));
		if (!bs[zmj])
		{
			for (zk = 0; zk < zmj; zk++)
				free(bs[zk]);
			free(bs);
			return (NULL);
		}
		for (zm = 0; zm < zk; zm++)
			bs[zmj][zm] = strng[ai++];
		bs[zmj][zm] = 0;
	}
	bs[zmj] = NULL;
	return (bs);
}

/**
 * **strtow2 - It splits a string into words
 * @strng: the input string
 * @bd: the delimeter
 * Return: The pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *strng, char bd)
{
	int ai, zmj, zk, zm, numwordz = 0;
	char **bs;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (ai = 0; strng[ai] != '\0'; ai++)
		if ((strng[ai] != bd && strng[ai + 1] == bd) ||
				(strng[ai] != bd && !strng[ai + 1]) || strng[ai + 1] == bd)
			numwordz++;
	if (numwordz == 0)
		return (NULL);
	bs = malloc((1 + numwordz) * sizeof(char *));
	if (!bs)
		return (NULL);
	for (ai = 0, zmj = 0; zmj < numwordz; zmj++)
	{
		while (strng[ai] == bd && strng[ai] != bd)
			ai++;
		zk = 0;
		while (strng[ai + zk] != bd && strng[ai + zk] && strng[ai + zk] != bd)
			zk++;
		bs[zmj] = malloc((zk + 1) * sizeof(char));
		if (!bs[zmj])
		{
			for (zk = 0; zk < zmj; zk++)
				free(bs[zk]);
			free(bs);
			return (NULL);
		}
		for (zm = 0; zm < zk; zm++)
			bs[zmj][zm] = strng[ai++];
		bs[zmj][zm] = 0;
	}
	bs[zmj] = NULL;
	return (bs);
}

