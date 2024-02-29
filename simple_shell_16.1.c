#include "simple_shell.h"

/**
 * _strcpy - It copies a string
 * @bdest: the destination
 * @bsrc: the source
 *
 * Return: The pointer to destination
 */
char *_strcpy(char *bdest, char *bsrc)
{
	int ai = 0;

	if (bdest == bsrc || bsrc == 0)
		return (bdest);
	while (bsrc[ai])
	{
		bdest[ai] = bsrc[ai];
		ai++;
	}
	bdest[ai] = 0;
	return (bdest);
}

/**
 * _strdup - It duplicates a string
 * @strng: the string to duplicate
 *
 * Return: The pointer to the duplicated string
 */
char *_strdup(const char *strng)
{
	int lengthz = 0;
	char *retz;

	if (strng == NULL)
		return (NULL);
	while (*strng++)
		lengthz++;
	retz = malloc(sizeof(char) * (lengthz + 1));
	if (!retz)
		return (NULL);
	for (lengthz++; lengthz--;)
		retz[lengthz] = *--strng;
	return (retz);
}

/**
 * _puts - It prints an input string
 * @strng: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strng)
{
	int ai = 0;

	if (!strng)
		return;
	while (strng[ai] != '\0')
	{
		_putchar(strng[ai]);
		ai++;
	}
}

/**
 * _putchar - It writes the character c to stdout
 * @ac: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putchar(char ac)
{
	static int ai;
	static char buff[WRITE_BUF_SIZE];

	if (ac == BUF_FLUSH || ai >= WRITE_BUF_SIZE)
	{
		write(1, buff, ai);
		ai = 0;
	}
	if (ac != BUF_FLUSH)
		buff[ai++] = ac;
	return (1);
}

