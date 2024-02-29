#include "simple_shell.h"

/**
 **_strncpy - It copies a string
 *@destn: the destination string to be copied to
 *@srcz: the source string
 *@zn: the amount of characters to be copied
 *Return: the string concatenated
 */
char *_strncpy(char *destn, char *srcz, int zn)
{
	int ai, bmj;
	char *msz = destn;

	ai = 0;
	while (srcz[ai] != '\0' && ai < zn - 1)
	{
		destn[ai] = srcz[ai];
		ai++;
	}
	if (ai < zn)
	{
		bmj = ai;
		while (bmj < zn)
		{
			destn[bmj] = '\0';
			bmj++;
		}
	}
	return (msz);
}

/**
 **_strncat - It concatenates two strings
 *@destn: the first string
 *@srcz: the second string
 *@zn: the amount of bytes to be maximally used
 *Return: the string concatenated
 */
char *_strncat(char *destn, char *srcz, int zn)
{
	int ai, bmj;
	char *msz = destn;

	ai = 0;
	bmj = 0;
	while (destn[ai] != '\0')
		ai++;
	while (srcz[bmj] != '\0' && bmj < zn)
	{
		destn[ai] = srcz[bmj];
		ai++;
		bmj++;
	}
	if (bmj < zn)
		destn[ai] = '\0';
	return (msz);
}

/**
 **_strchr - It locates a character in a string
 *@msz: the string to be parsed
 *@mcz: the character to look for
 *Return: (s) The pointer to the memory area s
 */
char *_strchr(char *msz, char mcz)
{
	do {
		if (*msz == mcz)
			return (msz);
	} while (*msz++ != '\0');

	return (NULL);
}

