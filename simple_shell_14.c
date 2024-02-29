#include "simple_shell.h"

/**
 * _memset - It fills memory with a constant byte
 * @zs: the pointer to the memory area
 * @zb: the byte to fill *s with
 * @zn: the amount of bytes to be filled
 * Return: (s) The  pointer to the memory area s
 */
char *_memset(char *zs, char zb, unsigned int zn)
{
	unsigned int ai;

	for (ai = 0; ai < zn; ai++)
		zs[ai] = zb;
	return (zs);
}

/**
 * ffree - It frees a string of strings
 * @zpp: The string of strings
 */
void ffree(char **zpp)
{
	char **za = zpp;

	if (!zpp)
		return;
	while (*zpp)
		free(*zpp++);
	free(za);
}

/**
 * _realloc - It reallocates a block of memory
 * @bptr: The pointer to previous malloc'ated block
 * @old_sizez: The byte size of previous block
 * @new_sizez: The byte size of new block
 *
 * Return: The pointer to the old'block name.
 */
void *_realloc(void *bptr, unsigned int old_sizez, unsigned int new_sizez)
{
	char *bp;

	if (!bptr)
		return (malloc(new_sizez));
	if (!new_sizez)
		return (free(bptr), NULL);
	if (new_sizez == old_sizez)
		return (bptr);

	bp = malloc(new_sizez);
	if (!bp)
		return (NULL);

	old_sizez = old_sizez < new_sizez ? old_sizez : new_sizez;
	while (old_sizez--)
		bp[old_sizez] = ((char *)bptr)[old_sizez];
	free(bptr);
	return (bp);
}

