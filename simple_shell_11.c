#include "simple_shell.h"

/**
 * main - the main entry point
 * @actr: the arg count
 * @avtr: the arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int actr, char **avtr)
{
	info_t information[] = { INFO_INIT };
	int zfd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (zfd)
			: "r" (zfd));

	if (actr == 2)
	{
		zfd = open(avtr[1], O_RDONLY);
		if (zfd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(avtr[0]);
				_eputs(": 0: Can not open ");
				_eputs(avtr[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = zfd;
	}
	populate_env_list(information);
	read_history(information);
	hsh(information, avtr);
	return (EXIT_SUCCESS);
}

