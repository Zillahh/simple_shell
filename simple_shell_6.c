#include "simple_shell.h"

/**
 * input_buf - The buffers chained commands
 * @information: The parameter struct
 * @buff: The address of buffer
 * @lenz: The address of len var
 *
 * Return: The bytes read
 */
ssize_t input_buf(info_t *information, char **buff, size_t *lenz)
{
	ssize_t br = 0;
	size_t len_pp = 0;

	if (!*lenz) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		br = getline(buff, &len_pp, stdin);
#else
		br = _getline(information, buff, &len_pp);
#endif
		if (br > 0)
		{
			if ((*buff)[br - 1] == '\n')
			{
				(*buff)[br - 1] = '\0'; /* remove trailing newline */
				br--;
			}
			information->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(information, *buff, information->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*lenz = br;
				information->cmd_buf = buff;
			}
		}
	}
	return (br);
}

/**
 * get_input - it gets a line minus the newline
 * @information: The parameter struct
 *
 * Return: The bytes read
 */
ssize_t get_input(info_t *information)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t ai, zmj, lenz;
	ssize_t br = 0;
	char **buf_pp = &(information->arg), *pp;

	_putchar(BUF_FLUSH);
	br = input_buf(information, &buff, &lenz);
	if (br == -1) /* EOF */
		return (-1);
	if (lenz) /* we have commands left in the chain buffer */
	{
		zmj = ai; /* init new iterator to current buf position */
		pp = buff + ai; /* get pointer for return */

		check_chain(information, buff, &zmj, ai, lenz);
		while (zmj < lenz) /* iterate to semicolon or end */
		{
			if (is_chain(information, buff, &zmj))
				break;
			zmj++;
		}

		ai = zmj + 1; /* increment past nulled ';'' */
		if (ai >= lenz) /* reached end of buffer? */
		{
			ai = lenz = 0; /* reset position and length */
			information->cmd_buf_type = CMD_NORM;
		}

		*buf_pp = pp; /* pass back pointer to current command position */
		return (_strlen(pp)); /* return length of current command */
	}

	*buf_pp = buff; /* else not a chain, pass back buffer from _getline() */
	return (br); /* return length of buffer from _getline() */
}

/**
 * read_buf - It reads a buffer
 * @information: The parameter struct
 * @buff: The buffer
 * @ai: The size
 *
 * Return: r
 */
ssize_t read_buf(info_t *information, char *buff, size_t *ai)
{
	ssize_t br = 0;

	if (*ai)
		return (0);
	br = read(information->readfd, buff, READ_BUF_SIZE);
	if (br >= 0)
		*ai = br;
	return (br);
}

/**
 * _getline - it gets the next line of input from STDIN
 * @information: The parameter struct
 * @ptrz: The address of pointer to buffer, preallocated or NULL
 * @lengthz: The size of preallocated ptrz buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *information, char **ptrz, size_t *lengthz)
{
	static char buff[READ_BUF_SIZE];
	static size_t ai, lenz;
	size_t mk;
	ssize_t br = 0, zs = 0;
	char *pp = NULL, *new_pp = NULL, *mc;

	pp = *ptrz;
	if (pp && lengthz)
		zs = *lengthz;
	if (ai == lenz)
		ai = lenz = 0;

	br = read_buf(information, buff, &lenz);
	if (br == -1 || (br == 0 && lenz == 0))
		return (-1);

	mc = _strchr(buff + ai, '\n');
	mk = mc ? 1 + (unsigned int)(mc - buff) : lenz;
	new_pp = _realloc(pp, zs, zs ? zs + mk : mk + 1);
	if (!new_pp) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (zs)
		_strncat(new_pp, buff + ai, mk - ai);
	else
		_strncpy(new_pp, buff + ai, mk - ai + 1);

	zs += mk - ai;
	ai = mk;
	pp = new_pp;

	if (lengthz)
		*lengthz = zs;
	*ptrz = pp;
	return (zs);
}

/**
 * sigintHandler - it blocks ctrl-C
 * @sig_numz: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_numz)
{
	_puts("\n");
	_puts("Zillahh$ ");
	_putchar(BUF_FLUSH);
}

