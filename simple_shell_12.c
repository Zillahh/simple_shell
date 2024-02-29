#include "simple_shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @bptr: the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **bptr)
{
	if (bptr && *bptr)
	{
		free(*bptr);
		*bptr = NULL;
		return (1);
	}
	return (0);
}

