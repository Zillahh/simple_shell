#include "simple_shell.h"

/**
 * _erratoi - It converts a string to an integer
 * @msz: the string to be converted
 * Return: 0 if no numbers in string
 * converted number otherwise
 *       -1 on error
 */
int _erratoi(char *msz)
{
	int ai = 0;
	unsigned long int resultz = 0;

	if (*msz == '+')
		msz++;  /* TODO: why does this make main return 255? */
	for (ai = 0;  msz[ai] != '\0'; ai++)
	{
		if (msz[ai] >= '0' && msz[ai] <= '9')
		{
			resultz *= 10;
			resultz += (msz[ai] - '0');
			if (resultz > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resultz);
}

/**
 * print_error - It prints an error message
 * @information: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string
 * converted number otherwise
 *        -1 on error
 */
void print_error(info_t *information, char *errstr)
{
	_eputs(information->fname);
	_eputs(": ");
	print_d(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_d - This function prints a decimal (integer) number (base 10)
 * @inputz: the input
 * @bzfd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int inputz, int bzfd)
{
	int (*__putchar)(char) = _putchar;
	int ai, countz = 0;
	unsigned int _absm_, currentz;

	if (bzfd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inputz < 0)
	{
		_absm_ = -inputz;
		__putchar('-');
		countz++;
	}
	else
		_absm_ = inputz;
	currentz = _absm_;
	for (ai = 1000000000; ai > 1; ai /= 10)
	{
		if (_absm_ / ai)
		{
			__putchar('0' + currentz / ai);
			countz++;
		}
		currentz %= ai;
	}
	__putchar('0' + currentz);
	countz++;

	return (countz);
}

/**
 * convert_number - It converter function, a clone of itoa
 * @bnumz: The number
 * @bbase: base
 * @bflags: The argument flags
 *
 * Return: string
 */
char *convert_number(long int bnumz, int bbase, int bflags)
{
	static char *arrayz;
	static char buffer[50];
	char signz = 0;
	char *bptr;
	unsigned long zn = bnumz;

	if (!(bflags & CONVERT_UNSIGNED) && bnumz < 0)
	{
		zn = -bnumz;
		signz = '-';

	}
	arrayz = bflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	bptr = &buffer[49];
	*bptr = '\0';

	do	{
		*--bptr = arrayz[zn % bbase];
		zn /= bbase;
	} while (zn != 0);

	if (signz)
		*--bptr = signz;
	return (bptr);
}

/**
 * remove_comments - This function replaces first instance of '#' with '\0'
 * @buff: The address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int ai;

	for (ai = 0; buff[ai] != '\0'; ai++)
		if (buff[ai] == '#' && (!ai || buff[ai - 1] == ' '))
		{
			buff[ai] = '\0';
			break;
		}
}

