#include "simple_shell.h"

/**
 * is_cmd - It determines if a file is an executable command
 * @information: the info struct
 * @pathz: path to the file
 *
 * Return: 1 if true or 0 otherwise
 */
int is_cmd(info_t *information, char *pathz)
{
	struct stat stz;

	(void)information;
	if (!pathz || stat(pathz, &stz))
		return (0);

	if (stz.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - It duplicates characters
 * @pathstrng: the PATH string
 * @startz: the starting index
 * @stopz: the stopping index
 *
 * Return: the pointer to new buffer
 */
char *dup_chars(char *pathstrng, int startz, int stopz)
{
	static char buf[1024];
	int ai = 0, mk = 0;

	for (mk = 0, ai = startz; ai < stopz; ai++)
		if (pathstrng[ai] != ':')
			buf[mk++] = pathstrng[ai];
	buf[mk] = 0;
	return (buf);
}

/**
 * find_path - It finds this cmd in the PATH string
 * @information: the info struct
 * @pathstrng: the PATH string
 * @cmdz: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *information, char *pathstrng, char *cmdz)
{
	int ai = 0, curr_poss = 0;
	char *pathz;

	if (!pathstrng)
		return (NULL);
	if ((_strlen(cmdz) > 2) && starts_with(cmdz, "./"))
	{
		if (is_cmd(information, cmdz))
			return (cmdz);
	}
	while (1)
	{
		if (!pathstrng[ai] || pathstrng[ai] == ':')
		{
			pathz = dup_chars(pathstrng, curr_poss, ai);
			if (!*pathz)
				_strcat(pathz, cmdz);
			else
			{
				_strcat(pathz, "/");
				_strcat(pathz, cmdz);
			}
			if (is_cmd(information, pathz))
				return (pathz);
			if (!pathstrng[ai])
				break;
			curr_poss = ai;
		}
		ai++;
	}
	return (NULL);
}

