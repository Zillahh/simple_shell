#include "simple_shell.h"

/**
 * _strlen - It returns the length of a string
 * @zs: the string whose length to check
 *
 * Return: The integer length of string
 */
int _strlen(char *zs)
{
	int ai = 0;

	if (!zs)
		return (0);

	while (*zs++)
		ai++;
	return (ai);
}

/**
 * _strcmp -It  performs lexicogarphic comparison of two strings.
 * @zs1: the first string
 * @zs2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *zs1, char *zs2)
{
	while (*zs1 && *zs2)
	{
		if (*zs1 != *zs2)
			return (*zs1 - *zs2);
		zs1++;
		zs2++;
	}
	if (*zs1 == *zs2)
		return (0);
	else
		return (*zs1 < *zs2 ? -1 : 1);
}

/**
 * starts_with - It checks if needle starts with haystack
 * @haystackz: The string to search
 * @needlez: the substring to find
 *
 * Return: The address of next char of haystack or NULL
 */
char *starts_with(const char *haystackz, const char *needlez)
{
	while (*needlez)
		if (*needlez++ != *haystackz++)
			return (NULL);
	return ((char *)haystackz);
}

/**
 * _strcat - It concatenates two strings
 * @bdest: the destination buffer
 * @bsrc: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *bdest, char *bsrc)
{
	char *retz = bdest;

	while (*bdest)
		bdest++;
	while (*bsrc)
		*bdest++ = *bsrc++;
	*bdest = *bsrc;
	return (retz);
}

