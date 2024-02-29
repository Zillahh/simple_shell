#include "simple_shell.h"

/**
 * interactive - it returns true if shell is interactive mode
 * @information: The struct address
 *
 * Return: 1 if interactive mode or 0 otherwise
 */
int interactive(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

/**
 * is_delim - it checks if character is a delimeter or not
 * @bcz: the char to check for
 * @delimz: the delimeter string
 * Return: 1 if true or 0 if false
 */
int is_delim(char bcz, char *delimz)
{
	while (*delimz)
		if (*delimz++ == bcz)
			return (1);
	return (0);
}

/**
 * _isalpha - it checks for alphabetic character
 * @bcz: The character to input in
 * Return: 1 if c is alphabetic or 0 otherwise
 */

int _isalpha(int bcz)
{
	if ((bcz >= 'a' && bcz <= 'z') || (bcz >= 'A' && bcz <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @strng: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *strng)
{
	int ai, signz = 1, flagz = 0, outputz;
	unsigned int resultz = 0;

	for (ai = 0; strng[ai] != '\0' && flagz != 2; ai++)
	{
		if (strng[ai] == '-')
			signz *= -1;

		if (strng[ai] >= '0' && strng[ai] <= '9')
		{
			flagz = 1;
			resultz *= 10;
			resultz += (strng[ai] - '0');
		}
		else if (flagz == 1)
			flagz = 2;
	}

	if (signz == -1)
		outputz = -resultz;
	else
		outputz = resultz;

	return (outputz);
}

