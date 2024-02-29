#include "simple_shell.h"

/**
 * get_history_file - gets the history file
 * @information: the parameter struct
 *
 * Return: the allocated string containg the history file
 */

char *get_history_file(info_t *information)
{
	char *buff, *dirtry;

	dirtry = _getenv(information, "HOME=");
	if (!dirtry)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirtry) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirtry);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - it creates a file, or appends to an existing file
 * @information: the parameter struct
 *
 * Return: 1 on success, else return -1
 */
int write_history(info_t *information)
{
	ssize_t bfd;
	char *filenamez = get_history_file(information);
	list_t *nodez = NULL;

	if (!filenamez)
		return (-1);

	bfd = open(filenamez, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenamez);
	if (bfd == -1)
		return (-1);
	for (nodez = information->history; nodez; nodez = nodez->next)
	{
		_putsfd(nodez->str, bfd);
		_putfd('\n', bfd);
	}
	_putfd(BUF_FLUSH, bfd);
	close(bfd);
	return (1);
}

/**
 * read_history - it reads history from file
 * @information: the parameter struct
 *
 * Return: history count on success, 0 otherwise
 */
int read_history(info_t *information)
{
	int ai, last = 0, linecount = 0;
	ssize_t bfd, brdlen, bfsize = 0;
	struct stat stz;
	char *buff = NULL, *filenamez = get_history_file(information);

	if (!filenamez)
		return (0);

	bfd = open(filenamez, O_RDONLY);
	free(filenamez);
	if (bfd == -1)
		return (0);
	if (!fstat(bfd, &stz))
		bfsize = stz.st_size;
	if (bfsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (bfsize + 1));
	if (!buff)
		return (0);
	brdlen = read(bfd, buff, bfsize);
	buff[bfsize] = 0;
	if (brdlen <= 0)
		return (free(buff), 0);
	close(bfd);
	for (ai = 0; ai < bfsize; ai++)
		if (buff[ai] == '\n')
		{
			buff[ai] = 0;
			build_history_list(information, buff + last, linecount++);
			last = ai + 1;
		}
	if (last != ai)
		build_history_list(information, buff + last, linecount++);
	free(buff);
	information->histcount = linecount;
	while (information->histcount-- >= HIST_MAX)
		delete_node_at_index(&(information->history), 0);
	renumber_history(information);
	return (information->histcount);
}

/**
 * build_history_list - it adds entry to a history linked list
 * @information: The Structure containing potential arguments.
 * @buff: the buffer
 * @linecountz: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *information, char *buff, int linecountz)
{
	list_t *nodez = NULL;

	add_node_end(&nodez, buff, linecountz);

	if (!information->history)
		information->history = nodez;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @information: The Structure containing potential arguments. Used to maintain
 *
 * Return: the new history count
 */
int renumber_history(info_t *information)
{
	list_t *nodez = information->history;
	int ai = 0;

	while (nodez)
	{
		nodez->num = ai++;
		nodez = nodez->next;
	}
	return (information->histcount = ai);
}

