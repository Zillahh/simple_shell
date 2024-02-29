#include "simple_shell.h"

/**
 * _eputs - It prints an input string
 * @strng: the string to be printed
 *
 * Return: void
 */
void _eputs(char *strng)
{
	int ai = 0;

	if (!strng)
		return;
	while (strng[ai] != '\0')
	{
		_eputchar(strng[ai]);
		ai++;
	}
}

/**
 * _eputchar - It writes the character c to stderr
 * @mcz: The character to print
 *
 * Return: On success 1.
 * On error -1 is returned
 * and errno is set appropriately.
 */
int _eputchar(char mcz)
{
	static int ai;
	static char buf[WRITE_BUF_SIZE];

	if (mcz == BUF_FLUSH || ai >= WRITE_BUF_SIZE)
	{
		write(2, buf, ai);
		ai = 0;
	}
	if (mcz != BUF_FLUSH)
		buf[ai++] = mcz;
	return (1);
}

/**
 * _putfd - It writes the character c to given fd
 * @mcz: The character to print
 * @bzfd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error -1 is returned
 * and errno is set appropriately.
 */
int _putfd(char mcz, int bzfd)
{
	static int ai;
	static char buf[WRITE_BUF_SIZE];

	if (mcz == BUF_FLUSH || ai >= WRITE_BUF_SIZE)
	{
		write(bzfd, buf, ai);
		ai = 0;
	}
	if (mcz != BUF_FLUSH)
		buf[ai++] = mcz;
	return (1);
}

/**
 * _putsfd - It prints an input string
 * @strng: the string to be printed
 * @bzfd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *strng, int bzfd)
{
	int ai = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		ai += _putfd(*strng++, bzfd);
	}
	return (ai);
}

